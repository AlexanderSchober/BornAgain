// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFunctionalTest.cpp
//! @brief     Implements class GUIFunctionalTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIFunctionalTest.h"
#include "SimulationRegistry.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "MaterialSvc.h"
#include "MaterialModel.h"
#include "Instrument.h"
#include "DomainObjectBuilder.h"
#include "SessionItem.h"
#include "IntensityDataFunctions.h"
#include "DomainSimulationBuilder.h"
#include "DocumentModel.h"
#include "Utils.h"

#include <QDebug>


GUIFunctionalTest::GUIFunctionalTest(const std::string &name, const std::string &description,
                                     GISASSimulation *reference_simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
{
}

GUIFunctionalTest::~GUIFunctionalTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void GUIFunctionalTest::runTest()
{
    if (!m_reference_simulation) {
        throw NullPointerException(
            "AdvancedGUIFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }

    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();
}

int GUIFunctionalTest::analyseResults()
{
    const std::unique_ptr<OutputData<double> > P_domain_data(m_domain_simulation->getDetectorIntensity());
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    return m_result;
}

void GUIFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
}


//! returns new simulation from
void GUIFunctionalTest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());

    // initializing necessary GUI
    const std::unique_ptr<DocumentModel> documentModel(new DocumentModel());
    const std::unique_ptr<SampleModel> sampleModel(new SampleModel());
    const std::unique_ptr<InstrumentModel> instrumentModel(new InstrumentModel());
    const std::unique_ptr<MaterialModel> materialModel(new MaterialModel());
    const std::unique_ptr<MaterialSvc> materialSvc(new MaterialSvc(materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(sampleModel.get(), *m_reference_simulation);
    guiBuilder.populateInstrumentModel(instrumentModel.get(), *m_reference_simulation);
    guiBuilder.populateDocumentModel(documentModel.get(), *m_reference_simulation);

    m_domain_simulation = DomainSimulationBuilder::getSimulation(sampleModel->multiLayerItem(),
            instrumentModel->instrumentItem(), documentModel->getSimulationOptionsItem());
}
