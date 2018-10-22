// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/SimulationBuilder.cpp
//! @brief     Implements class SimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjectiveBuilder.h"
#include "JobItem.h"
#include "Parameters.h"
#include "KernelTypes.h"
#include "FitObjective.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "FitParameterItems.h"
#include "RealDataItem.h"
#include "GUIHelpers.h"
#include "DataItem.h"
#include "OutputData.h"
#include "DomainSimulationBuilder.h"
#include "FitSuiteItem.h"
#include "MinimizerItem.h"
#include "IMinimizer.h"
#include "Minimizer.h"

FitObjectiveBuilder::FitObjectiveBuilder(JobItem* jobItem)
    : m_jobItem(jobItem)
{
    Q_ASSERT(m_jobItem->fitSuiteItem());
}

void FitObjectiveBuilder::runFit()
{
    auto objective = createFitObjective();
    fcn_scalar_t scalar_func = [&](const Fit::Parameters& params) {
        return objective->evaluate(params);
    };

    Fit::Minimizer minimizer;
    minimizer.setMinimizer(createMinimizer().release());

    auto result = minimizer.minimize(scalar_func, createParameters());
    objective->finalize(result);
}

std::unique_ptr<FitObjective> FitObjectiveBuilder::createFitObjective() const
{
    std::unique_ptr<FitObjective> result(new FitObjective);

    simulation_builder_t builder = [&](const Fit::Parameters& params) {
        return buildSimulation(params);
    };

    result->addSimulationAndData(builder, *createOutputData(), 1.0);

    return result;
}

std::unique_ptr<IMinimizer> FitObjectiveBuilder::createMinimizer() const
{
    auto fitSuiteItem = m_jobItem->fitSuiteItem();
    return fitSuiteItem->minimizerContainerItem()->createMinimizer();
}

Fit::Parameters FitObjectiveBuilder::createParameters() const
{
    auto fitSuiteItem = m_jobItem->fitSuiteItem();
    return fitSuiteItem->fitParameterContainerItem()->createParameters();
}

std::unique_ptr<Simulation> FitObjectiveBuilder::buildSimulation(const Fit::Parameters& params) const
{
    update_fit_parameters(params);
    return DomainSimulationBuilder::createSimulation(m_jobItem->multiLayerItem(),
            m_jobItem->instrumentItem(), m_jobItem->simulationOptionsItem());
}

std::unique_ptr<OutputData<double> > FitObjectiveBuilder::createOutputData() const
{
    auto realDataItem = m_jobItem->realDataItem();
    if(!realDataItem)
        throw GUIHelpers::Error("FitObjectiveBuilder::createOutputData() -> No Real Data defined.");

    const DataItem* intensity_item = realDataItem->dataItem();
    Q_ASSERT(intensity_item);
    Q_ASSERT(intensity_item->getOutputData());

    return std::unique_ptr<OutputData<double>>(intensity_item->getOutputData()->clone());
}


void FitObjectiveBuilder::update_fit_parameters(const Fit::Parameters& params) const
{
    QVector<double> values = GUIHelpers::fromStdVector(params.values());

    auto fitParContainer = m_jobItem->fitParameterContainerItem();
    fitParContainer->setValuesInParameterContainer(values, m_jobItem->parameterContainerItem());
}
