// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobResultsPresenter.cpp
//! @brief     Implements class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobResultsPresenter.h"
#include "IntensityProjectionsWidget.h"
#include "FitComparisonWidget.h"
#include "JobItem.h"
#include "IntensityDataWidget.h"
#include "mainwindow_constants.h"

JobResultsPresenter::JobResultsPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(Constants::IntensityDataWidgetName, create_new<IntensityDataWidget>);

    registerWidget(Constants::IntensityProjectionsWidgetName,
                   create_new<IntensityProjectionsWidget>);

    registerWidget(Constants::FitComparisonWidgetName, create_new<FitComparisonWidget>);
}

//! Returns list of presentation types, available for given item. JobItem with fitting abilities
//! is valid for IntensityDataWidget and FitComparisonWidget.

QStringList JobResultsPresenter::activePresentationList(SessionItem* item)
{
    JobItem* jobItem = dynamic_cast<JobItem*>(item);
    Q_ASSERT(jobItem);

    QStringList result = QStringList() << Constants::IntensityDataWidgetName
                                       << Constants::IntensityProjectionsWidgetName;

    if (jobItem->isValidForFitting())
        result << Constants::FitComparisonWidgetName;

    return result;
}
