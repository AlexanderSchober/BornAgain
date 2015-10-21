// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Simulation.h"

#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "DWBASimulation.h"
#include "MessageService.h"
#include "OutputDataFunctions.h"
#include "BornAgainNamespace.h"
#include "ProgressHandlerDWBA.h"
#include "OMPISimulation.h"

#include "Macros.h"
GCC_DIAG_OFF(strict-aliasing);
#include <boost/thread.hpp>
GCC_DIAG_ON(strict-aliasing);
#include <gsl/gsl_errno.h>
#include <boost/scoped_ptr.hpp>

Simulation::Simulation()
    : IParameterized("Simulation"), mp_options(0)
{
    init_parameters();
}

Simulation::Simulation(const ProgramOptions *p_options)
    : IParameterized("Simulation"), mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(const ISample &p_sample, const ProgramOptions *p_options)
    : IParameterized("Simulation"), mp_options(p_options)
{
    mP_sample.reset(p_sample.clone());
    init_parameters();
}

Simulation::Simulation(SampleBuilder_t p_sample_builder, const ProgramOptions *p_options)
    : IParameterized("Simulation"), mp_sample_builder(p_sample_builder), mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(const Simulation &other)
    : ICloneable(), IParameterized(other), mp_sample_builder(other.mp_sample_builder),
      m_sim_params(other.m_sim_params), m_thread_info(other.m_thread_info),
      mp_options(other.mp_options), m_distribution_handler(other.m_distribution_handler),
      m_progress(other.m_progress)
{
    if (other.mP_sample.get())
        mP_sample.reset(other.mP_sample->clone());
    init_parameters();
}

void Simulation::init_parameters()
{
}

void Simulation::prepareSimulation()
{
    gsl_set_error_handler_off();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    prepareSimulation();

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    if (m_progress) m_progress->init(this, param_combinations);

    // no averaging needed:
    if (param_combinations == 1) {
        boost::scoped_ptr<ParameterPool> P_param_pool(createParameterTree());
        m_distribution_handler.setParameterValues(P_param_pool.get(), 0);
        runSingleSimulation();
        transferResultsToIntensityMap();
        return;
    }

    // average over parameter distributions:
    initSimulationElementVector();
    std::vector<SimulationElement> total_intensity = m_sim_elements;
    boost::scoped_ptr<ParameterPool> P_param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(P_param_pool.get(), index);
        runSingleSimulation();
        AddElementsWithWeight(m_sim_elements.begin(), m_sim_elements.end(), total_intensity.begin(),
                              weight);
    }
    m_sim_elements = total_intensity;
    transferResultsToIntensityMap();
}

void Simulation::runOMPISimulation()
{
    OMPISimulation ompi;
    ompi.runSimulation(this);
}

//! The ISample object will not be owned by the Simulation object
void Simulation::setSample(const ISample &sample)
{
    mP_sample.reset(sample.clone());
}

void Simulation::setSampleBuilder(SampleBuilder_t p_sample_builder)
{
    if (!p_sample_builder.get())
        throw NullPointerException("Simulation::setSampleBuilder() -> "
                                   "Error! Attempt to set null sample builder.");

    mp_sample_builder = p_sample_builder;
    mP_sample.reset(0);
}

std::string Simulation::addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    if (mp_sample_builder.get()) {
        // add parameters of the sample builder
        mp_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    } else if (mP_sample.get()) {
        // add parameters of directly the sample
        mP_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Simulation::addParameterDistribution(const std::string &param_name,
                                          const IDistribution1D &distribution, size_t nbr_samples,
                                          double sigma_factor, const AttLimits &limits)
{
    m_distribution_handler.addParameterDistribution(param_name, distribution, nbr_samples,
                                                    sigma_factor, limits);
}

void Simulation::addParameterDistribution(const ParameterDistribution &par_distr)
{
    m_distribution_handler.addParameterDistribution(par_distr);
}

const DistributionHandler &Simulation::getDistributionHandler() const
{
    return m_distribution_handler;
}

double Simulation::getWavelength() const
{
    throw RuntimeErrorException(
        "Simulation::getWavelength: not uniquely defined for this type of Simulation");
}

void Simulation::updateSample()
{
    if (mp_sample_builder.get()) {
        ISample *p_new_sample = mp_sample_builder->buildSample();
        std::string builder_type = typeid(*mp_sample_builder).name();
        if (builder_type.find("ISampleBuilder_wrapper") != std::string::npos) {
            msglog(MSG::DEBUG2) << "Simulation::updateSample() -> "
                                   "OMG, some body has called me from python, what an idea... ";
            setSample(*p_new_sample);
        } else {
            mP_sample.reset(p_new_sample);
        }
    }
}

//! Run single simulation with fixed parameter values.
//! Also manage threads.
void Simulation::runSingleSimulation()
{
    updateSample();
    initSimulationElementVector();

    // retrieve batch and threading information
    if (mp_options) {
        if (mp_options->find("nbatches")) {
            m_thread_info.n_batches = (*mp_options)["nbatches"].as<int>();
        }
        if (mp_options->find("currentbatch")) {
            m_thread_info.current_batch = (*mp_options)["currentbatch"].as<int>();
        }
        if (mp_options->find("threads")) {
            m_thread_info.n_threads = (*mp_options)["threads"].as<int>();
        }
    }

    // restrict calculation to current batch
    std::vector<SimulationElement>::iterator batch_start
        = getBatchStart(m_thread_info.n_batches, m_thread_info.current_batch);
    std::vector<SimulationElement>::iterator batch_end
        = getBatchEnd(m_thread_info.n_batches, m_thread_info.current_batch);

    if (m_thread_info.n_threads < 0)
        m_thread_info.n_threads = 1;
    if (m_thread_info.n_threads == 1) {
        // Single thread.
        boost::scoped_ptr<DWBASimulation> P_dwba_simulation(mP_sample->createDWBASimulation());
        verifyDWBASimulation(P_dwba_simulation.get());
        P_dwba_simulation->init(*this, batch_start, batch_end);
        P_dwba_simulation->run(); // the work is done here
        if (!P_dwba_simulation->isCompleted()) {
            std::string message = P_dwba_simulation->getRunMessage();
            throw Exceptions::RuntimeErrorException("Simulation::runSimulation() -> Simulation has "
                                                    "terminated unexpectedly with following error "
                                                    "message.\n" + message);
        }
    } else {
        // Multithreading.
        if (m_thread_info.n_threads == 0) {
            // Take optimal number of threads from the hardware.
            m_thread_info.n_threads = (int)boost::thread::hardware_concurrency();
            msglog(MSG::DEBUG) << "Simulation::runSimulation() -> Info. Number of threads "
                               << m_thread_info.n_threads << " (taken from hardware concurrency)"
                               << ", n_batches = " << m_thread_info.n_batches
                               << ", current_batch = " << m_thread_info.current_batch;
        } else {
            msglog(MSG::DEBUG) << "Simulation::runSimulation() -> Info. Number of threads "
                               << m_thread_info.n_threads << " (ordered by user)"
                               << ", n_batches = " << m_thread_info.n_batches
                               << ", current_batch = " << m_thread_info.current_batch;
        }
        std::vector<boost::thread *> threads;
        std::vector<DWBASimulation *> simulations;

        // Initialize n simulations.
        int total_batch_elements = batch_end - batch_start;
        int element_thread_step = total_batch_elements / m_thread_info.n_threads;
        if (total_batch_elements % m_thread_info.n_threads) ++element_thread_step;
        for (int i_thread = 0; i_thread < m_thread_info.n_threads; ++i_thread) {
            if (i_thread*element_thread_step >= total_batch_elements) break;
            DWBASimulation *p_dwba_simulation = mP_sample->createDWBASimulation();
            verifyDWBASimulation(p_dwba_simulation);
            std::vector<SimulationElement>::iterator begin_it = batch_start
                                                                + i_thread * element_thread_step;
            std::vector<SimulationElement>::iterator end_it;
            int end_thread_index = (i_thread + 1)*element_thread_step;
            if (end_thread_index >= total_batch_elements) {
                end_it = batch_end;
            } else {
                end_it = batch_start + end_thread_index;
            }
            p_dwba_simulation->init(*this, begin_it, end_it);
            simulations.push_back(p_dwba_simulation);
        }

        // Run simulations in n threads.
        for (std::vector<DWBASimulation *>::iterator it = simulations.begin();
             it != simulations.end(); ++it) {
            threads.push_back(new boost::thread(boost::bind(&DWBASimulation::run, *it)));
        }

        // Wait for threads to complete.
        for (size_t i = 0; i < threads.size(); ++i) {
            threads[i]->join();
        }

        // Merge simulated data.
        bool isSuccess(true);
        std::string failure_message;
        for (size_t i = 0; i < simulations.size(); ++i) {
            if (!simulations[i]->isCompleted()) {
                isSuccess = false;
                failure_message = simulations[i]->getRunMessage();
            }
            delete simulations[i];
            delete threads[i];
        }
        if (!isSuccess) {
            throw Exceptions::RuntimeErrorException(
                "Simulation::runSingleSimulation() -> Simulation has terminated unexpectedly "
                "with the following error message.\n" + failure_message);
        }
    }
    normalize(batch_start, batch_end);
}

void Simulation::normalize(std::vector<SimulationElement>::iterator begin_it,
                           std::vector<SimulationElement>::iterator end_it) const
{
    double beam_intensity = getBeamIntensity();
    // no normalization when beam intensity is zero:
    if (beam_intensity==0.0) return;
    for(std::vector<SimulationElement>::iterator it=begin_it; it!=end_it; ++it) {
        double sin_alpha_i = std::abs(std::sin(it->getAlphaI()));
        if (sin_alpha_i==0.0) sin_alpha_i = 1.0;
        double solid_angle = it->getSolidAngle();
        it->setIntensity(it->getIntensity()*beam_intensity*solid_angle/sin_alpha_i);
    }
}

void Simulation::initProgressHandlerDWBA(ProgressHandlerDWBA *dwba_progress)
{
    // if we have external ProgressHandler (which is normally coming from GUI),
    // then we will create special callbacks for every DWBASimulation.
    // These callback will be used to report DWBASimulation progress to the Simulation.
    if (m_progress) {
        ProgressHandler::Callback_t callback
            = boost::bind(&ProgressHandler::update, m_progress.get(), _1);
        dwba_progress->setCallback(callback);
    }
}

void Simulation::verifyDWBASimulation(DWBASimulation *dwbaSimulation)
{
    if (!dwbaSimulation)
        throw RuntimeErrorException(
            "Simulation::runSimulation() -> Can't create the simulation for given sample."
            "It should be either the MultiLayer with more than one layer (with or without "
            "particles),"
            "or MultiLayer with single Layer containing particles.");
}

std::vector<SimulationElement>::iterator Simulation::getBatchStart(int n_batches, int current_batch)
{
    imposeConsistencyOfBatchNumbers(n_batches, current_batch);
    int total_size = m_sim_elements.size();
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches) ++size_per_batch;
    if (current_batch*size_per_batch >= total_size) return m_sim_elements.end();
    return m_sim_elements.begin() + current_batch*size_per_batch;
}

std::vector<SimulationElement>::iterator Simulation::getBatchEnd(int n_batches, int current_batch)
{
    imposeConsistencyOfBatchNumbers(n_batches, current_batch);
    int total_size = m_sim_elements.size();
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches) ++size_per_batch;
    int end_index = (current_batch + 1)*size_per_batch;
    if (end_index >= total_size) return m_sim_elements.end();
    return m_sim_elements.begin() + end_index;
}

void Simulation::imposeConsistencyOfBatchNumbers(int &n_batches, int &current_batch)
{
    if (n_batches < 2) {
        n_batches = 1;
        current_batch = 0;
    }
    if (current_batch >= n_batches) {
        throw ClassInitializationException(
            "Simulation::imposeConsistencyOfBatchNumbers(): Batch number must be smaller than "
            "number of batches.");
    }
}
