// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/IntensityProjectionsWidget.h
//! @brief     Defines class IntensityProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobProjectionsWidget.h"
#include "IntensityDataItem.h"
#include "ProjectionItems.h"
#include "SessionModel.h"
#include "JobItem.h"
#include "ProjectionsEditor.h"
#include "RealDataItem.h"
#include "GUIHelpers.h"
#include <QVBoxLayout>

JobProjectionsWidget::JobProjectionsWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_projectionsEditor(new ProjectionsEditor)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_projectionsEditor);

    setLayout(vlayout);
}

void JobProjectionsWidget::setItem(SessionItem* jobItem)
{
    SessionItemWidget::setItem(jobItem);

    auto projectionContainer = createProjectionContainer(intensityDataItem());

    m_projectionsEditor->setContext(intensityDataItem()->model(),
                                    projectionContainer->index(), intensityDataItem());
}

QList<QAction*> JobProjectionsWidget::actionList()
{
    return m_projectionsEditor->topToolBarActions();
}

IntensityDataItem* JobProjectionsWidget::intensityDataItem()
{
    if (!currentItem())
        throw GUIHelpers::Error("JobProjectionsWidget::intensityDataItem() -> Error. "
                                "Not initialized.");

    if (currentItem()->modelType() == Constants::JobItemType)
        return &currentItem()->item<IntensityDataItem>(JobItem::T_OUTPUT);
    else if(currentItem()->modelType() == Constants::RealDataType)
        return &currentItem()->item<IntensityDataItem>(RealDataItem::T_INTENSITY_DATA);
    else if(currentItem()->modelType() == Constants::IntensityDataType)
        return dynamic_cast<IntensityDataItem *>(currentItem());
    else
        throw GUIHelpers::Error("JobProjectionsWidget::intensityDataItem() -> Error. "
                                "Unexpected item.");
}

ProjectionContainerItem*
JobProjectionsWidget::createProjectionContainer(IntensityDataItem* intensityItem)
{
    Q_ASSERT(intensityItem);

    auto containerItem = intensityItem->getItem(IntensityDataItem::T_PROJECTIONS);
    if (!containerItem)
        containerItem = intensityItem->model()->insertNewItem(Constants::ProjectionContainerType,
                                                              intensityItem->index(), -1,
                                                              IntensityDataItem::T_PROJECTIONS);

    return dynamic_cast<ProjectionContainerItem*>(containerItem);
}


