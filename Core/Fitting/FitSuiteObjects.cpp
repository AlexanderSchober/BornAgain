// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteObjects.cpp
//! @brief     Implements class FitSuiteObjects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitSuiteObjects.h"
#include "ChiSquaredModule.h"
#include "Histogram2D.h"

static_assert(std::is_copy_constructible<FitSuiteObjects>::value == false,
    "FitSuiteObjects should not be copy constructable");
static_assert(std::is_copy_assignable<FitSuiteObjects>::value == false,
    "FitSuiteObjects should not be copy assignable");

FitSuiteObjects::FitSuiteObjects()
  : m_total_weight(0)
   ,m_nfree_parameters(0)
  , m_chi_squared_value(0)
  , m_chi2_module(new ChiSquaredModule())
  , m_fit_elements_count(0)
{
    setName("FitSuite"); // deliberately made as in FitSuite
    init_parameters();
}

FitSuiteObjects::~FitSuiteObjects()
{
}

FitObject* FitSuiteObjects::add(
    const Simulation& simulation, const OutputData<double>& real_data, double weight)
{
    m_total_weight += weight;
    FitObject *result = new FitObject(simulation, real_data, weight);
    registerChild(result);
    m_fit_elements_count += result->numberOfFitElements();
    m_fit_objects.push_back(result);
    return result;
}

//! Returns total number of data points
size_t FitSuiteObjects::getSizeOfDataSet() const
{
    return m_fit_elements_count;
}

void FitSuiteObjects::setChiSquaredModule(const IChiSquaredModule& chi2_module)
{
    m_chi2_module.reset(chi2_module.clone());
}

SimulationResult FitSuiteObjects::simulationResult(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->simulationResult();
}

SimulationResult FitSuiteObjects::experimentalData(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->experimentalData();
}

//! loop through all defined simulations and run them
void FitSuiteObjects::runSimulations()
{
    if(getSizeOfDataSet() == 0) {
        std::ostringstream message;
        message << "FitSuiteObjects::runSimulations() -> Error. Zero size of dataset.";
        throw Exceptions::LogicErrorException(message.str());
    }

    m_fit_elements.clear();
    m_fit_elements.reserve(getSizeOfDataSet());

    for(auto it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it)
        (*it)->prepareFitElements(m_fit_elements, (*it)->weight()/m_total_weight,
                                  m_chi2_module->getIntensityNormalizer());

    if(m_fit_elements.size() != getSizeOfDataSet()) {
        std::ostringstream message;
        message << "FitSuiteObjects::runSimulations() -> Error. Dataset size mismatch. "
                << " m_fit_elements.size():" << m_fit_elements.size()
                << " getSizeOfDataset():" << getSizeOfDataSet() << std::endl;
        throw Exceptions::LogicErrorException(message.str());
    }

    m_chi_squared_value = calculateChiSquaredValue();
}

double FitSuiteObjects::getResidualValue(size_t global_index)
{
    if(global_index >= m_fit_elements.size())
        throw Exceptions::LogicErrorException(
            "FitSuiteObjects::getResidualValue() -> Error. Index exceeds size of dataset.");
    return m_fit_elements[global_index].getResidual();
}

void FitSuiteObjects::clear()
{
    m_fit_objects.clear();
    m_fit_elements.clear();
}

std::vector<const INode*> FitSuiteObjects::getChildren() const
{
    std::vector<const INode*> result;
    for(auto fitObject : m_fit_objects)
        result.push_back(fitObject);

    if(m_chi2_module) {
        const IIntensityNormalizer* data_normalizer = m_chi2_module->getIntensityNormalizer();
        if(data_normalizer)
            result.push_back(data_normalizer);
    }

    return result;
}

std::unique_ptr<IHistogram> FitSuiteObjects::createChiSquaredHistogram(size_t i_item) const
{
    // copying shape and axes labels from SimulationResults
    auto result = m_fit_objects[check_index(i_item)]->simulationResult();
    std::unique_ptr<OutputData<double>> buff(result.data());
    buff->setAllTo(0.0);

    for(std::vector<FitElement>::const_iterator it=getStart(i_item); it!=getEnd(i_item); ++it)
        (*buff)[it->getIndex()] = it->getSquaredDifference();

    return std::unique_ptr<IHistogram>(IHistogram::createHistogram(*buff));
}

double FitSuiteObjects::calculateChiSquaredValue()
{
    m_chi2_module->processFitElements(m_fit_elements.begin(), m_fit_elements.end());

    double result(0);
    for (auto it = m_fit_elements.begin(); it != m_fit_elements.end(); ++it)
        result += it->getSquaredDifference();

    int fnorm = static_cast<int>(m_fit_elements.size()) - m_nfree_parameters;
    if (fnorm <= 0)
        throw Exceptions::LogicErrorException(
            "FitSuiteObjects::calculateChiSquaredValue() -> Error. Normalization is 0");
    return result / fnorm;
}

size_t FitSuiteObjects::check_index(size_t index) const
{
    if( index >= m_fit_objects.size() )
        throw Exceptions::OutOfBoundsException("FitSuiteKit::check() -> Index outside of range");
    return index;
}

//! Returns iterator pointing to the begin of FitObject with given i_item index.

std::vector<FitElement>::const_iterator FitSuiteObjects::getStart(size_t i_item) const
{
    check_index(i_item);

    int istart(0);
    for(size_t i=0; i<i_item; ++i)
        istart += m_fit_objects[i]->numberOfFitElements();

    return m_fit_elements.begin() + istart;
}

std::vector<FitElement>::const_iterator FitSuiteObjects::getEnd(size_t i_item) const
{
    return getStart(i_item) + static_cast<int>(m_fit_objects[i_item]->numberOfFitElements());
}
