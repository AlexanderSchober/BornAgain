// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformToDomain.cpp
//! @brief     Implements class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TransformToDomain.h"
#include "BeamAngleItems.h"
#include "BeamItem.h"
#include "BeamWavelengthItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"
#include "Distributions.h"
#include "FTDecayFunctionItems.h"
#include "FTDistributionItems.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionItems.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "Lattice2DItems.h"
#include "LayerItem.h"
#include "LayerRoughnessItems.h"
#include "MaskItems.h"
#include "MaterialUtils.h"
#include "MesoCrystal.h"
#include "MesoCrystalItem.h"
#include "MultiLayerItem.h"
#include "ParameterPattern.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "RotationItems.h"
#include "SimulationOptionsItem.h"
#include "TransformationItem.h"
#include "Particle.h"
#include "Units.h"
#include "VectorItem.h"
#include "ParticleCoreShell.h"

std::unique_ptr<Material> TransformToDomain::createDomainMaterial(const SessionItem& item)
{
    MaterialProperty material_property;
    if (item.modelType() == Constants::ParticleType) {
        material_property
            = item.getItemValue(ParticleItem::P_MATERIAL).value<MaterialProperty>();
    } else if (item.modelType() == Constants::LayerType) {
        material_property
            = item.getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    }
    if (!material_property.isDefined())
        throw GUIHelpers::Error(
            "TransformToDomain::createDomainMaterial() -> Error. Can't create material "
            "for item '"+item.displayName()+"'.");

    return MaterialUtils::createDomainMaterial(material_property);
}

std::unique_ptr<MultiLayer> TransformToDomain::createMultiLayer(const SessionItem& item)
{
    auto P_multilayer = std::make_unique<MultiLayer>();
    auto cross_corr_length
        = item.getItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH).toDouble();
    if (cross_corr_length > 0)
        P_multilayer->setCrossCorrLength(cross_corr_length);
    auto external_field = item.getVectorItem(MultiLayerItem::P_EXTERNAL_FIELD);
    P_multilayer->setExternalField(external_field);
    return P_multilayer;
}

std::unique_ptr<Layer> TransformToDomain::createLayer(const SessionItem& item)
{
    auto P_layer = std::make_unique<Layer>(
        *createDomainMaterial(item),
        item.getItemValue(LayerItem::P_THICKNESS).toDouble());
    P_layer->setNumberOfSlices(item.getItemValue(LayerItem::P_NSLICES).toUInt());
    return P_layer;
}

std::unique_ptr<LayerRoughness>
TransformToDomain::createLayerRoughness(const SessionItem& roughnessItem)
{
    if (roughnessItem.modelType() == Constants::LayerZeroRoughnessType) {
        return nullptr;
    } else if (roughnessItem.modelType() == Constants::LayerBasicRoughnessType) {
        return std::make_unique<LayerRoughness>(
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_SIGMA).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_HURST).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH)
                .toDouble());
    } else {
        throw GUIHelpers::Error("TransformToDomain::createLayerRoughness() -> Error.");
    }
}

std::unique_ptr<ParticleLayout>
TransformToDomain::createParticleLayout(const SessionItem& item)
{
    auto P_layout = std::make_unique<ParticleLayout>();
    auto prop = item.getItemValue(ParticleLayoutItem::P_APPROX).value<ComboProperty>();
    QString approximation = prop.getValue();
    if (approximation == Constants::LAYOUT_DA) {
        P_layout->setApproximation(ILayout::DA);
    } else if (approximation == Constants::LAYOUT_SSCA) {
        P_layout->setApproximation(ILayout::SSCA);
    }
    auto total_density
        = item.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).value<double>();
    P_layout->setTotalParticleSurfaceDensity(total_density);
    return P_layout;
}

std::unique_ptr<IParticle> TransformToDomain::createIParticle(const SessionItem& item)
{
    std::unique_ptr<IParticle> P_particle;
    if (item.modelType() == Constants::ParticleType) {
        auto& particle_item = static_cast<const ParticleItem&>(item);
        P_particle = particle_item.createParticle();
    } else if (item.modelType() == Constants::ParticleCoreShellType) {
        auto& particle_coreshell_item = static_cast<const ParticleCoreShellItem&>(item);
        P_particle = particle_coreshell_item.createParticleCoreShell();
    } else if (item.modelType() == Constants::ParticleCompositionType) {
        auto& particle_composition_item = static_cast<const ParticleCompositionItem&>(item);
        P_particle = particle_composition_item.createParticleComposition();
    } else if (item.modelType() == Constants::MesoCrystalType) {
        auto& mesocrystal_item = static_cast<const MesoCrystalItem&>(item);
        P_particle = mesocrystal_item.createMesoCrystal();
    }
    return P_particle;
}

std::unique_ptr<ParticleDistribution> TransformToDomain::createParticleDistribution(
        const SessionItem& item)
{
    auto& particle_distribution = static_cast<const ParticleDistributionItem&>(item);
    auto P_part_distr = particle_distribution.createParticleDistribution();
    return P_part_distr;
}

//! adds DistributionParameters to the Simulation
void TransformToDomain::addDistributionParametersToSimulation(const SessionItem& beam_item,
                                                              GISASSimulation* simulation)
{
    ParameterPattern pattern_wavelength;
    pattern_wavelength.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
    ParameterPattern pattern_alpha;
    pattern_alpha.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
    ParameterPattern pattern_phi;
    pattern_phi.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Azimuth);
    if (beam_item.modelType() == Constants::BeamType) {
        if (auto beamWavelength
            = dynamic_cast<BeamWavelengthItem*>(beam_item.getItem(BeamItem::P_WAVELENGTH))) {
            auto P_par_distr = beamWavelength->getParameterDistributionForName(
                        pattern_wavelength.toStdString());
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
        if (auto inclinationAngle = dynamic_cast<BeamInclinationAngleItem*>(
                beam_item.getItem(BeamItem::P_INCLINATION_ANGLE))) {
            auto P_par_distr = inclinationAngle->getParameterDistributionForName(
                        pattern_alpha.toStdString());
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
        if (auto azimuthalAngle = dynamic_cast<BeamAzimuthalAngleItem*>(
                beam_item.getItem(BeamItem::P_AZIMUTHAL_ANGLE))) {
            auto P_par_distr = azimuthalAngle->getParameterDistributionForName(
                        pattern_phi.toStdString());
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
    }
}

void TransformToDomain::setSimulationOptions(GISASSimulation* simulation,
                                             const SessionItem& item)
{
    Q_ASSERT(item.modelType() == Constants::SimulationOptionsType);

    if (auto optionItem = dynamic_cast<const SimulationOptionsItem*>(&item)) {
        simulation->getOptions().setNumberOfThreads(optionItem->getNumberOfThreads());
        if (optionItem->getComputationMethod() == Constants::SIMULATION_MONTECARLO) {
            simulation->getOptions().setMonteCarloIntegration(true,
                    optionItem->getNumberOfMonteCarloPoints());
        }
        if (optionItem->getFresnelMaterialMethod() == Constants::AVERAGE_LAYER_MATERIAL)
            simulation->getOptions().setUseAvgMaterials(true);
        if (optionItem->getIncludeSpecularPeak() == Constants::Yes)
            simulation->getOptions().setIncludeSpecular(true);
    }
}

void TransformToDomain::setTransformationInfo(IParticle* result, const SessionItem& item)
{
    setPositionInfo(result, item);
    setRotationInfo(result, item);
}

void TransformToDomain::setPositionInfo(IParticle* result, const SessionItem& item)
{
    kvector_t pos = item.getVectorItem(ParticleItem::P_POSITION);
    result->setPosition(pos.x(), pos.y(), pos.z());
}

void TransformToDomain::setRotationInfo(IParticle* result, const SessionItem& item)
{
    QVector<SessionItem*> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::TransformationType) {
            auto& rot_item = children[i]->groupItem<RotationItem>(TransformationItem::P_ROT);
            auto rotation = rot_item.createRotation();
            if (rotation)
                result->setRotation(*rotation);
            break;
        }
    }
}
