// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformToDomain.h
//! @brief     Defines class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMTODOMAIN_H
#define TRANSFORMTODOMAIN_H

#include "Samples.h"
#include "InterferenceFunctions.h"
#include "ParameterizedItem.h"
#include "Instrument.h"

#include <memory>

namespace TransformToDomain
{
BA_CORE_API_ std::unique_ptr<IMaterial> createDomainMaterial(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<MultiLayer> createMultiLayer(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<Layer> createLayer(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<LayerRoughness> createLayerRoughness(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<ParticleLayout> createParticleLayout(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<IFormFactor> createFormFactor(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<IDistribution1D> createDistribution(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<IInterferenceFunction> createInterferenceFunction(
        const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<Instrument> createInstrument(const ParameterizedItem &item);
BA_CORE_API_ std::unique_ptr<Beam> createBeam(const ParameterizedItem &item);
BA_CORE_API_ void initInstrumentFromDetectorItem(const ParameterizedItem &item,
                                                 Instrument *instrument);
BA_CORE_API_ void addDistributionParametersToSimulation(const ParameterizedItem &beam_item,
                                                        GISASSimulation *simulation);
BA_CORE_API_ void setTransformationInfo(IParticle *result, const ParameterizedItem &item);
BA_CORE_API_ void setPositionInfo(IParticle *result, const ParameterizedItem &item);
BA_CORE_API_ void setRotationInfo(IParticle *result, const ParameterizedItem &item);
}

#endif // TRANSFORMTODOMAIN_H
