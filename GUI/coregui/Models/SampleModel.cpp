// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleModel.cpp
//! @brief     Implements class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SampleModel.h"
#include "MultiLayerItem.h"

SampleModel::SampleModel(QObject* parent)
    : SessionModel(SessionXML::SampleModelTag, parent)
{
    setObjectName(SessionXML::SampleModelTag);
}

SampleModel* SampleModel::createCopy(SessionItem* parent)
{
    SampleModel* result = new SampleModel();
    result->initFrom(this, parent);
    return result;
}

MultiLayerItem* SampleModel::multiLayerItem(const QString& item_name)
{
    return dynamic_cast<MultiLayerItem*>(topItem(Constants::MultiLayerType, item_name));
}
