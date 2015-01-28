// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedGraphicsItem.cpp
//! @brief     Implements class ParameterizedGraphicsItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedGraphicsItem.h"


const QString ParameterizedGraphicsItem::P_XPOS = "xpos";
const QString ParameterizedGraphicsItem::P_YPOS = "ypos";


ParameterizedGraphicsItem::ParameterizedGraphicsItem(const QString &model_type,
                           ParameterizedItem *parent)
    : ParameterizedItem(model_type, parent)
{
    registerProperty(P_XPOS, qreal(0.0), PropertyAttribute::hiddenProperty());
    registerProperty(P_YPOS, qreal(0.0), PropertyAttribute::hiddenProperty());
}

