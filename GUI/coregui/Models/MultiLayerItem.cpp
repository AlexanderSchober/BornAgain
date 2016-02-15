// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MultiLayerItem.cpp
//! @brief     Implements class MultiLayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "ScientificDoubleProperty.h"
#include <QDebug>

const QString MultiLayerItem::P_CROSS_CORR_LENGTH = "Cross Correlation Length";

MultiLayerItem::MultiLayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::MultiLayerType, parent)
{
    registerProperty(P_CROSS_CORR_LENGTH, 0.0);
    addToValidChildren(Constants::LayerType);
    registerProperty(P_NAME, Constants::MultiLayerType);
}

ParameterizedItem *MultiLayerItem::takeChildItem(int row)
{
    ParameterizedItem *item = ParameterizedItem::takeChildItem(row);
    updateLayers();
    return item;
}

void MultiLayerItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    updateLayers();
}

void MultiLayerItem::updateLayers()
{
    for(int i = 0; i<childItemCount(); ++i) {
        if(i == 0) {
            childAt(i)->getPropertyAttribute(LayerItem::P_ROUGHNESS).setDisabled();
        } else {
            childAt(i)->getPropertyAttribute(LayerItem::P_ROUGHNESS).setVisible();
        }
        if(i==0 || i==childItemCount()-1) {
            childAt(i)->getPropertyAttribute(LayerItem::P_THICKNESS).setDisabled();
        } else {
            childAt(i)->getPropertyAttribute(LayerItem::P_THICKNESS).setVisible();
        }
    }
}
