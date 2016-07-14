// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/TransformationView.cpp
//! @brief     Implements class TransformationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DesignerHelper.h"
#include "item_constants.h"
#include "TransformationView.h"


TransformationView::TransformationView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::TransformationType);
    setColor(DesignerHelper::getDefaultTransformationColor());
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::TRANSFORMATION);
    m_roundpar = 3;
}
