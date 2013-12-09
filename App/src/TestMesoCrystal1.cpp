// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestMesoCrystal1.cpp
//! @brief     Implements class TestMesoCrystal1.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMesoCrystal1.h"
#include "SimulationRegistry.h"
#include "Types.h"
#include "Utils.h"
#include "DrawHelper.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"

void TestMesoCrystal1::execute()
{

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("mesocrystal01");

    // loading reference data
    //std::string filename = Utils::FileSystem::GetPathToData("../Tests/ReferenceData/BornAgain/")+ "mesocrystal1b_reference.txt.gz";
    //std::string filename = "dev-tools/tmp-examples/MesoCrystals/ex02_fitspheres/004_230_P144_im_full_phitheta.txt.gz";
    std::string filename = Utils::FileSystem::GetReferenceDataDir()+ "mesocrystal1_reference_v2_nphi180.txt.gz";
    //std::string filename = Utils::FileSystem::GetPathToData("../Tests/ReferenceData/BornAgain/")+ "mesocrystal1_reference_v2_nphi2.txt.gz";

    OutputData<double> *reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->setProgramOptions(mp_options);

    // setting detector axis as in reference data
    simulation->setDetectorParameters(*reference);

    simulation->getSampleBuilder()->setParameterValue("nphi_rotations", 180.);

    simulation->runSimulation();
    simulation->normalize();

    OutputData<double> *data = simulation->getIntensityData();

    TCanvas *c1 = DrawHelper::createAndRegisterCanvas("sim_meso_crystal",
            "mesocrystal", 1024, 768);
    c1->cd(); gPad->SetLogz();

    TH2D *h2 = IsGISAXSTools::getOutputDataTH2D(*data, "mesocrystal");
    h2->SetTitle("");
    h2->GetXaxis()->SetTitle("#phi_{f}");
    h2->GetYaxis()->SetTitle("#alpha_{f}");
    h2->GetXaxis()->SetTitleOffset(0.9);
    h2->GetYaxis()->SetTitleOffset(1.0);
    h2->SetMinimum(100.);
    h2->SetMaximum(1e6);
    h2->Draw("COLZ");

    IsGISAXSTools::drawOutputDataComparisonResults(
            *data, *reference, "found", "found params", 100, 1e6);

    OutputDataIOFactory::writeIntensityData(*data,"test_mesocrystal1.txt");
    delete data;

    delete simulation;
    delete reference;
}

