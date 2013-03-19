// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/FitSuiteObjects.cpp
//! @brief     Implements class FitSuiteObjects.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FitSuiteObjects.h"

FitSuiteObjects::FitSuiteObjects() : m_total_weight(0), m_simulation_normalize(false), m_nfree_parameters(0), m_chi_squared_value(0)
{
    setName("FitSuiteObjects");
    init_parameters();
}

//! clear all data
void FitSuiteObjects::clear()
{
    m_fit_objects.clear();
}

//! add to kit pair of (simulation, real data) for consecutive simulation and chi2 module
void FitSuiteObjects::add(const Simulation &simulation, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module, double weight)
{
    m_total_weight += weight;
    m_fit_objects.push_back(new FitObject(simulation, real_data, chi2_module, weight));
}

//! loop through all defined simulations and run them
void FitSuiteObjects::runSimulations()
{
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        (*it)->getSimulation()->runSimulation();
        if(m_simulation_normalize) (*it)->getSimulation()->normalize();
    }
    m_chi_squared_value = calculateChiSquaredValue();
}

//! get total number of data points
size_t FitSuiteObjects::getSizeOfDataSet() const
{
    size_t result(0);
    for(FitObjects_t::const_iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        result += (*it)->getSizeOfData();
    }
    return result;
}

//! ?
const FitObject *FitSuiteObjects::getObjectForGlobalDataIndex(size_t global_index, size_t &local_index)
{
    local_index = global_index;
    for(FitObjects_t::const_iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        if(local_index < (*it)->getSizeOfData() ) {
            return (*it);
        } else if(local_index >= (*it)->getSizeOfData() ) {
            local_index -= (*it)->getSizeOfData();
        }
    }
    std::ostringstream ostr;
    ostr << "FitSuiteObjects::getObjectForGlobalDataIndex() -> Error! Can't find fit object for given global data index " << global_index;
    throw LogicErrorException(ostr.str());
}

//! get sum of chi squared values for all fit objects
double FitSuiteObjects::calculateChiSquaredValue()
{
    double result(0);
    double max_intensity = getSimulationMaxIntensity();
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        IChiSquaredModule *chi = (*it)->getChiSquaredModule();

        chi->setNdegreeOfFreedom( (int)(m_fit_objects.size() * (*it)->getRealData()->getAllocatedSize() - m_nfree_parameters) );
        // normalizing datasets to the maximum intensity over all fit objects defined
        if( chi->getOutputDataNormalizer() ) {
            chi->getOutputDataNormalizer()->setMaximumIntensity(max_intensity);
        }

        double weight = (*it)->getWeight()/m_total_weight;
        double chi_squared = (weight*weight) * (*it)->calculateChiSquared();
        result += chi_squared;
    }
    return result;
}

//! ?
double FitSuiteObjects::getResidualValue(size_t global_index)
{
    size_t index(0);
    const FitObject *fitObject = getObjectForGlobalDataIndex(global_index, index);
    double residual = fitObject->getChiSquaredModule()->getResidualValue(index)*(fitObject->getWeight()/m_total_weight);
    return residual;
}

//! calculate maximum intensity in simulated data over all fit objects defined
double FitSuiteObjects::getSimulationMaxIntensity()
{
    double result(0);
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        const OutputData<double > *data = (*it)->getSimulation()->getOutputData();
        OutputData<double >::const_iterator cit = std::max_element(data->begin(), data->end());
        result = std::max(result, *cit);
    }
    return result;
}

//! add parameters from local pool to external pool
std::string FitSuiteObjects::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    (void)copy_number;
    // add own parameters
    // so far it is top object in our chain, and its without parameters, lets not include its name in path
    //std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);
    std::string new_path = path;

    int ncopy(0);
    if(m_fit_objects.size()==1) ncopy=-1; // if we have only one object, lets get rid from copy number
    for(FitObjects_t::const_iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it, ++ncopy) {
        (*it)->addParametersToExternalPool(new_path, external_pool, ncopy);
    }

    return new_path;
}

//! ?
void FitSuiteObjects::init_parameters()
{
}
