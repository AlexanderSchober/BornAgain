// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/LayerItem.cpp
//! @brief     Implements class LayerItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerItem.h"
#include "LayerRoughnessItems.h"

const QString LayerItem::P_THICKNESS = "Thickness";
const QString LayerItem::P_ROUGHNESS = "Top roughness";

LayerItem::LayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::LayerType, parent)
{
    setItemName(Constants::LayerType);
    registerProperty(P_THICKNESS, 0.0);
    setMaterialProperty();

    registerFancyGroupProperty(P_ROUGHNESS, Constants::LayerRoughnessGroup);
    addToValidChildren(Constants::ParticleLayoutType, PortInfo::Port0, 1);
}
