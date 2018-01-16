// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainObjectBuilder.h
//! @brief     Defines class DomainObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H

#include "WinDllMacros.h"
#include <memory>

class Instrument;
class MultiLayer;
class Layer;
class ParticleLayout;
class IInterferenceFunction;
class Beam;
class SessionItem;
class InstrumentItem;

class BA_CORE_API_ DomainObjectBuilder
{
public:
    std::unique_ptr<MultiLayer> buildMultiLayer(const SessionItem &multilayer_item) const;
    std::unique_ptr<Layer> buildLayer(const SessionItem &item) const;
    std::unique_ptr<ParticleLayout> buildParticleLayout(const SessionItem &item) const;
    std::unique_ptr<IInterferenceFunction>
    buildInterferenceFunction(const SessionItem &item) const;
    std::unique_ptr<Instrument> buildInstrument(const InstrumentItem& instrumentItem) const;
};

#endif // DOMAINOBJECTBUILDER_H
