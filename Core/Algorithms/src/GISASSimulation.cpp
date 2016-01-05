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

#include "GISASSimulation.h"

#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "DWBASimulation.h"
#include "MessageService.h"
#include "OutputDataFunctions.h"
#include "BornAgainNamespace.h"
#include "ProgressHandlerDWBA.h"
#include "OMPISimulation.h"
#include "Histogram2D.h"

#include "Macros.h"
#include <gsl/gsl_errno.h>
#include <boost/scoped_ptr.hpp>

GISASSimulation::GISASSimulation()
: m_instrument()
, m_intensity_map()
{
    initialize();
}

GISASSimulation::GISASSimulation(const ProgramOptions *p_options)
: Simulation(p_options)
, m_instrument()
, m_intensity_map()
{
    initialize();
}

GISASSimulation::GISASSimulation(
    const ISample& p_sample, const ProgramOptions *p_options)
: Simulation(p_sample, p_options)
, m_instrument()
, m_intensity_map()
{
    initialize();
}

GISASSimulation::GISASSimulation(
    SampleBuilder_t p_sample_builder, const ProgramOptions *p_options)
: Simulation(p_sample_builder, p_options)
, m_instrument()
, m_intensity_map()
{
    initialize();
}

GISASSimulation *GISASSimulation::clone() const
{
    return new GISASSimulation(*this);
}

void GISASSimulation::prepareSimulation()
{
    if(m_instrument.getDetectorDimension() != 2) {
        throw LogicErrorException("GISASSimulation::prepareSimulation() "
                "-> Error. The detector was not properly configured.");
    }
    if (getWavelength() <= 0.0) {
        throw ClassInitializationException(
                "GISASSimulation::prepareSimulation() "
                "-> Error. Incoming wavelength <= 0.");
    }

    getInstrument().getDetector()->init(this);

    Simulation::prepareSimulation();
}

int GISASSimulation::getNumberOfSimulationElements() const
{
    if (m_instrument.getDetectorDimension()!=2) {
        throw RuntimeErrorException("GISASSimulation::getNumberOfSimulationElements: "
                                    "detector is not two-dimensional");
    }
    const IAxis &x_axis = m_instrument.getDetectorAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &y_axis = m_instrument.getDetectorAxis(BornAgain::X_AXIS_INDEX);
    int nmasked = getInstrument().getDetector()->getNumberOfMaskedChannels();
    return x_axis.getSize()*y_axis.getSize() - nmasked;
}

OutputData<double> *GISASSimulation::getDetectorIntensity() const
{
    OutputData<double> *result = m_intensity_map.clone();
    m_instrument.applyDetectorResolution(result);
    return result;
}

Histogram2D *GISASSimulation::getIntensityData() const
{
    boost::scoped_ptr<OutputData<double> > data(getDetectorIntensity());
    return new Histogram2D(*data);
}

void GISASSimulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMap();
}

void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength<=0.0) {
        throw ClassInitializationException(
                "Simulation::setBeamParameters() "
                "-> Error. Incoming wavelength <= 0.");
    }

    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
}

void GISASSimulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

void GISASSimulation::setBeamPolarization(const kvector_t &bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

void GISASSimulation::setDetector(const IDetector2D &detector)
{
    m_instrument.setDetector(detector);
    updateIntensityMap();
}

void GISASSimulation::setDetectorParameters(const OutputData<double >& output_data)
{
    m_instrument.matchDetectorAxes(output_data);

    m_intensity_map.clear();
    m_intensity_map.copyShapeFrom(output_data); // to copy mask too
    m_intensity_map.setAllTo(0.);
}

void GISASSimulation::setDetectorParameters(const IHistogram &hisotgram)
{
    boost::scoped_ptr<OutputData<double> > data(hisotgram.createOutputData());
    setDetectorParameters(*data);
}

void GISASSimulation::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                            size_t n_y, double y_min, double y_max)
{
    m_instrument.setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
    updateIntensityMap();
}

void GISASSimulation::setDetectorResolutionFunction(
    const IResolutionFunction2D &resolution_function)
{
    m_instrument.setDetectorResolutionFunction(resolution_function);
}

void GISASSimulation::removeDetectorResolutionFunction()
{
    m_instrument.setDetectorResolutionFunction(0);
}

void GISASSimulation::setAnalyzerProperties(const kvector_t &direction, double efficiency,
                                       double total_transmission)
{
    m_instrument.setAnalyzerProperties(direction, efficiency, total_transmission);
}

std::string GISASSimulation::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path =
        IParameterized::addParametersToExternalPool(
            path, external_pool, copy_number);

    // add parameters of the instrument
    m_instrument.addParametersToExternalPool(new_path, external_pool, -1);

    if (mp_sample_builder.get()) {
       // add parameters of the sample builder
        mp_sample_builder->addParametersToExternalPool(
            new_path, external_pool, -1);
    } else if (mP_sample.get()) {
        // add parameters of the existing sample
        mP_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

double GISASSimulation::getWavelength() const
{
    return m_instrument.getBeam().getWavelength();
}

void GISASSimulation::removeMasks()
{
    m_instrument.getDetector()->removeMasks();
}

void GISASSimulation::addMask(const Geometry::IShape2D &shape, bool mask_value)
{
    m_instrument.getDetector()->addMask(shape, mask_value);
}

void GISASSimulation::maskAll()
{
    m_instrument.getDetector()->maskAll();
}


GISASSimulation::GISASSimulation(const GISASSimulation& other)
: Simulation(other)
, m_instrument(other.m_instrument)
, m_intensity_map()
{
    m_intensity_map.copyFrom(other.m_intensity_map);

    initialize();
}

void GISASSimulation::init_parameters()
{
}

void GISASSimulation::initSimulationElementVector()
{
    m_sim_elements = m_instrument.createSimulationElements();
}

void GISASSimulation::transferResultsToIntensityMap()
{
    size_t detector_dimension = m_instrument.getDetectorDimension();
    if (detector_dimension!=2) {
        throw RuntimeErrorException("GISASSimulation::transferResultsToIntensityMap: "
                                    "detector is not two-dimensional");
    }
    updateIntensityMap();

    size_t element_index(0);
    for(size_t index=0; index<m_intensity_map.getAllocatedSize(); ++index) {
        if(m_instrument.getDetector()->isMasked(index)) continue;
        m_intensity_map[index] = m_sim_elements[element_index++].getIntensity();
    }
}

double GISASSimulation::getBeamIntensity() const
{
    return m_instrument.getBeamIntensity();
}

void GISASSimulation::updateIntensityMap()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
    }
    m_intensity_map.setAllTo(0.);
}

void GISASSimulation::initialize()
{
    setName(BornAgain::GISASSimulationType);
    init_parameters();
}
