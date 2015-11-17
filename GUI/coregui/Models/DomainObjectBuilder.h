// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainObjectBuilder.h
//! @brief     Defines class DomainObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H

#include "WinDllMacros.h"

#include <memory>

class ISample;
class Instrument;
class MultiLayer;
class Layer;
class ParticleLayout;
class IParticle;
class Particle;
class IInterferenceFunction;
class Beam;
class ParticleCoreShell;
class ParticleComposition;
class ParticleDistribution;
class ParameterizedItem;
class LayerRoughness;

class BA_CORE_API_ DomainObjectBuilder
{
public:
    std::unique_ptr<MultiLayer> buildMultiLayer(const ParameterizedItem &multilayer_item) const;
    std::unique_ptr<Layer> buildLayer(const ParameterizedItem &item) const;
    std::unique_ptr<ParticleLayout> buildParticleLayout(const ParameterizedItem &item) const;
    std::unique_ptr<Particle> buildParticle(const ParameterizedItem &item, double &abundance) const;
    std::unique_ptr<ParticleCoreShell> buildParticleCoreShell(const ParameterizedItem &item,
                                                              double &abundance) const;
    std::unique_ptr<ParticleComposition> buildParticleComposition(const ParameterizedItem &item,
                                                                  double &abundance) const;
    std::unique_ptr<ParticleDistribution> buildParticleDistribution(const ParameterizedItem &item,
                                                                    double &abundance) const;
    std::unique_ptr<IInterferenceFunction> buildInterferenceFunction(
            const ParameterizedItem &item) const;

    std::unique_ptr<Instrument> buildInstrument(const ParameterizedItem &instrument_item) const;
    std::unique_ptr<Beam> buildBeam(const ParameterizedItem &item) const;

private:
    void setTransformationInfo(IParticle *result, const ParameterizedItem &item) const;
    void setPositionInfo(IParticle *result, const ParameterizedItem &item) const;
    void setRotationInfo(IParticle *result, const ParameterizedItem &item) const;
};

#endif // DOMAINOBJECTBUILDER_H
