// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataViewUtils.h
//! @brief     Defines namespace DataViewUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATAVIEWUTILS_H
#define DATAVIEWUTILS_H

#include <memory>

class DataItem;
class DataItem1DView;
class JobItem;
template<class T> class OutputData;

namespace DataViewUtils
{
//! Initializes DataItem1DView and assigns it to the passed JobItem
void initDataView(JobItem* jobItem);

//! Sets units and axis labels to DataItem1DView.
//! The item should be attached to a valid JobItem.
void setUnitProperties(DataItem1DView* view_item);

std::unique_ptr<OutputData<double>> getTranslatedData(DataItem1DView* view_item,
                                                      DataItem* data_item);
};

#endif // DATAVIEWUTILS_H
