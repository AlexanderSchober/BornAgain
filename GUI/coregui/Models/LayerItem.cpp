// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerItem.cpp
//! @brief     Implements class LayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LayerItem.h"
#include "BornAgainNamespace.h"
#include "MaterialUtils.h"

const QString LayerItem::P_THICKNESS = QString::fromStdString(BornAgain::Thickness);
const QString LayerItem::P_ROUGHNESS = "Top roughness";
const QString LayerItem::P_MATERIAL = "Material";
const QString LayerItem::P_NSLICES = "Number of slices";
const QString LayerItem::T_LAYOUTS = "Layout tag";

LayerItem::LayerItem()
    : SessionGraphicsItem(Constants::LayerType)
{
    addProperty(P_THICKNESS, 0.0);
    getItem(P_THICKNESS)->setLimits(RealLimits::lowerLimited(0.0));

    addProperty(P_MATERIAL, MaterialUtils::getDefaultMaterialProperty().getVariant());

    addProperty(P_NSLICES, 1)->setLimits(RealLimits::lowerLimited(0.0));

    addGroupProperty(P_ROUGHNESS, Constants::LayerRoughnessGroup);

    registerTag(T_LAYOUTS, 0, -1, QStringList() << Constants::ParticleLayoutType);
    setDefaultTag(T_LAYOUTS);
}
