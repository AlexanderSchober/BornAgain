// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GUIExamplesFactory.cpp
//! @brief     Implements class GUIExamplesFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIExamplesFactory.h"
#include "GUIObjectBuilder.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "GUIHelpers.h"
#include "GISASSimulation.h"
#include <boost/scoped_ptr.hpp>
#include <QDebug>

//! Defines correspondance between example name and real name of simulation from SimulationRegistry
QMap<QString, QString > init_NameToRegistry()
{
    QMap<QString, QString > result;
    result["example01"] = "CylindersAndPrismsBuilder";
    result["example02"] = "RadialParaCrystalBuilder";
    result["example03"] = "TwoDimParaCrystalBuilder";
    result["example04"] = "CoreShellParticleBuilder";
    result["example05"] = "MultiLayerWithRoughnessBuilder";
    result["example06"] = "SquareLatticeBuilder";
    result["example07"] = "RotatedPyramidsBuilder";
    result["example08"] = "CylindersWithSizeDistributionBuilder";
    result["example09"] = "ParticleCompositionBuilder";

    // temporary for testing
    //result["example09"] = "MultipleLayoutBuilder";
    //result["example09"] = "TwoTypesCylindersDistributionBuilder";

    return result;
}

QMap<QString, QString> GUIExamplesFactory::m_name_to_registry = init_NameToRegistry();

bool GUIExamplesFactory::isValidExampleName(const QString &name)
{
    return m_name_to_registry.contains(name);
}

//! Populate sample model with
ParameterizedItem *GUIExamplesFactory::createSampleItems(const QString &name, SampleModel *sampleModel)
{
    QString exampleName = m_name_to_registry[name];

    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> sample(factory.createSample(exampleName.toStdString()));

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateSampleModel(sampleModel, *sample.get(), name);
}

//ParameterizedItem *GUIExamplesFactory::createInstrumentItems(const QString &name, InstrumentModel *instrumentModel)
//{
//    QString exampleName = m_name_to_registry[name];
//    SimulationRegistry registry;
//    boost::scoped_ptr<GISASSimulation> P_simulation(registry.createSimulation(exampleName.toStdString()));
//    Q_ASSERT(P_simulation.get());

//    QString instrumentName = name + "_instrument";
//    GUIObjectBuilder guiBuilder;
//    return guiBuilder.populateInstrumentModel(instrumentModel, *P_simulation, instrumentName);
//}
