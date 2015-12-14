// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SimulationRegistry.cpp
//! @brief     Implement class SimulationRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationRegistry.h"
#include "StandardSimulations.h"


SimulationRegistry::SimulationRegistry()
{
    registerItem("BasicGISAS", StandardSimulations::BasicGISAS,
                 "Basic GISAS simulation with the detector phi[0,2], theta[0,2]");

    registerItem("BasicGISAS00", StandardSimulations::BasicGISAS00,
                 "Basic GISAS for polarization studies");

    registerItem("MiniGISAS", StandardSimulations::MiniGISAS,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2]");

    registerItem("MiniGISASBeamDivergence", StandardSimulations::MiniGISASBeamDivergence,
                 "GISAS simulation with small detector and beam divergence");

    registerItem("MiniGISASDetectorResolution", StandardSimulations::MiniGISASDetectorResolution,
                 "GISAS simulation with small detector and detector resolution");


    registerItem("MiniGISASWithMasks", StandardSimulations::MiniGISASWithMasks,
                 "GISAS simulation with small detector and various masks");

    registerItem("MaxiGISAS", StandardSimulations::MaxiGISAS,
                 "GISAS simulation with large detector to test performance");
    registerItem("MaxiGISAS00", StandardSimulations::MaxiGISAS00,
                 "GISAS simulation with large detector to test performance");

    registerItem("IsGISAXSSimulation1", StandardSimulations::IsGISAXSSimulation1,
                 "Typical IsGISAXS simulation with the detector theta[-1,1], phi[0,2]");

    registerItem("IsGISAXSSimulation2", StandardSimulations::IsGISAXSSimulation2,
                 "Typical IsGISAXS simulation with the detector theta[0,1], phi[0,2]");

    // --- custom simulations ---
    registerItem(
        "polmagcylinders2", StandardSimulations::PolarizedDWBAMagCylinders2,
        "Polarized DWBA with non-zero magnetic field");

}


GISASSimulation *SimulationRegistry::createSimulation(const std::string& name)
{
    GISASSimulation *result = createItem(name);
    return result;
}


