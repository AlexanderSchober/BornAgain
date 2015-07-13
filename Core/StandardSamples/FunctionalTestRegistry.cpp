// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestRegistry.cpp
//! @brief     Implements class FunctionalTestRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestRegistry.h"
#include "Exceptions.h"
#include "Utils.h"


FunctionalTestRegistry::FunctionalTestRegistry()
{

    add("FormFactors",
        "Test of all form factors defined",
        "MiniGISAS",
        "ParticleInTheAirBuilder",
        "FormFactorsRegistry",
        2e-10);

    add("CylindersAndPrisms",
        "Mixture of cylinders and prisms without interference",
        "MiniGISAS",
        "CylindersAndPrismsBuilder",
        "None",
        2e-10);

    add("RadialParaCrystal",
        "Interference function of radial paracrystal",
        "MiniGISAS",
        "RadialParaCrystalBuilder",
        "None",
        2e-10);

    add("Basic2DParaCrystal",
        "Interference function of basic 2D paracrystal with variety of FT distributions",
        "MiniGISAS",
        "Basic2DParaCrystalBuilder",
        "FTDistributions2DRegistry",
        2e-10);

    add("HexParaCrystal",
        "Interference function of 2D hexagonal paracrystal",
        "MiniGISAS",
        "HexParaCrystalBuilder",
        "None",
        2e-10);

    add("RectParaCrystal",
        "Interference function of 2D rectanguler paracrystal",
        "MiniGISAS",
        "RectParaCrystalBuilder",
        "None",
        2e-10);

    add("CoreShellParticle",
        "Core shell particle",
        "MiniGISAS",
        "CoreShellParticleBuilder",
        "None",
        2e-10);

    add("MultiLayerWithRoughness",
        "Multilayer with roughness",
        "MiniGISAS",
        "MultiLayerWithRoughnessBuilder",
        "None",
        2e-10);

    add("SquareLattice",
        "Interference function of 2D square lattice",
        "MiniGISAS",
        "SquareLatticeBuilder",
        "None",
        2e-10);

    add("CenteredSquareLattice",
        "Interference function of 2D square lattice",
        "MiniGISAS",
        "CenteredSquareLatticeBuilder",
        "None",
        2e-10);

    add("RotatedSquareLattice",
        "Interference function of rotated 2D square lattice",
        "MiniGISAS",
        "RotatedSquareLatticeBuilder",
        "None",
        2e-10);

    add("RotatedPyramids",
        "Interference function of rotated 2D square lattice",
        "MiniGISAS",
        "RotatedPyramidsBuilder",
        "None",
        2e-10);

    add("ParticleComposition",
        "Two layers of spheres at hex lattice",
        "MiniGISAS",
        "ParticleCompositionBuilder",
        "None",
        2e-10);

    add("CylindersWithSizeDistribution",
        "Cylinders in BA with size distributions",
        "MiniGISAS",
        "CylindersWithSizeDistributionBuilder",
        "None",
        2e-10);

    add("TwoTypesCylindersDistribution",
        "Cylinders in BA with size distributions",
        "MiniGISAS",
        "TwoTypesCylindersDistributionBuilder",
        "None",
        2e-10);

    add("BeamDivergence",
        "Cylinders in BA in the presence of beam divergence",
        "MiniGISASBeamDivergence",
        "CylindersInBABuilder",
        "None",
        2e-10);

    add("DetectorResolution",
        "Cylinders in BA with detector resolution",
        "MiniGISASDetectorResolution",
        "CylindersInBABuilder",
        "None",
        2e-10);

    add("MultipleLayout",
        "Two types of particles in different layouts",
        "MiniGISAS",
        "MultipleLayoutBuilder",
        "None",
        2e-10);

    add("ApproximationDA",
        "Size distribution model: decoupling approximation",
        "MiniGISAS",
        "SizeDistributionDAModelBuilder",
        "None",
        2e-10);

    add("ApproximationLMA",
        "Size distribution model: local monodisperse approximation",
        "MiniGISAS",
        "SizeDistributionLMAModelBuilder",
        "None",
        2e-10);

    add("ApproximationSSCA",
        "Size distribution model: size space coupling approximation",
        "MiniGISAS",
        "SizeDistributionSSCAModelBuilder",
        "None",
        2e-10);

    add("CylindersInSSCA",
        "Size spacing correlation approximation",
        "MiniGISAS",
        "CylindersInSSCABuilder",
        "None",
        2e-10);

    add("CosineRipple",
        "Cosine ripple within radial paracrystal model",
        "MiniGISAS",
        "CosineRippleBuilder",
        "None",
        2e-10);

    add("TriangularRipple",
        "Triangular ripple within radial paracrystal model",
        "MiniGISAS",
        "TriangularRippleBuilder",
        "None",
        2e-10);

    add("MesoCrystal",
        "Cylindrical mesocrystal composed of spherical nano particles",
        "MiniGISASForMeso",
        "MesoCrystalBuilder",
        "None",
        2e-10);

    add("CustomMorphology",
        "Custom particle mixture a la isgisaxs morphology approach",
        "MiniGISAS",
        "CustomMorphologyBuilder",
        "None",
        2e-10);

    add("MagneticParticleZeroField",
        "Magnetic cylinders with zero field",
        "MiniGISAS",
        "MagneticParticleZeroFieldBuilder",
        "None",
        2e-10);

    add("TransformBox",
        "Rotated/translated box in 3 layers system",
        "MiniGISAS",
        "TransformBoxBuilder",
        "None",
        1e-10);

}

void FunctionalTestRegistry::add(const std::string &test_name,
                                 const std::string &test_description,
                                 const std::string &simulation_name,
                                 const std::string &sample_builder_name,
                                 const std::string &component_registry_name,
                                 double threshold)
{
    catalogue_t::iterator it = m_catalogue.find(test_name);
    if( it != m_catalogue.end() ) {
        throw ExistingClassRegistrationException("AdvancedFunctionalTestRegistry::register_test_info() -> "
                                                 "Error. Existing item " + test_name);
    }
    m_catalogue[test_name] = FunctionalTestInfo(test_name,
                                                        test_description,
                                                        simulation_name,
                                                        sample_builder_name,
                                                        component_registry_name,
                                                        threshold);
}

FunctionalTestInfo FunctionalTestRegistry::getTestInfo(const std::string &test_name)
{
    catalogue_t::iterator it = m_catalogue.find(test_name);
    if( it == m_catalogue.end() ) {
        throw ExistingClassRegistrationException("AdvancedFunctionalTestRegistry::getTestInfo() -> "
                                                 "Error. Item not found " + test_name);
    }

    return m_catalogue[test_name];
}

void FunctionalTestRegistry::printCatalogue(std::ostream &ostr)
{
    for(catalogue_t::const_iterator it = m_catalogue.begin(); it != m_catalogue.end(); ++it) {
        FunctionalTestInfo info = it->second;
        ostr << Utils::AdjustStringLength(info.m_test_name, 20) << " | ";
        ostr << Utils::AdjustStringLength(info.m_test_description, 40) << " | ";
        ostr << info.m_simulation_name << ", ";
        ostr << info.m_sample_builder_name << ", ";
        ostr << info.m_component_registry_name;
        ostr << "\n";
    }

}

bool FunctionalTestRegistry::isValidTest(const std::string &test_name)
{
    return find(test_name) != end();
}



