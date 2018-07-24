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
class Data1DViewItem;
class JobItem;
template<class T> class OutputData;

namespace DataViewUtils
{
//! Initializes Data1DViewItem and assigns it to the passed JobItem
void initDataView(JobItem* jobItem);

void updateAxesTitle(Data1DViewItem* view_item);

std::unique_ptr<OutputData<double>> getTranslatedData(Data1DViewItem* view_item,
                                                      DataItem* data_item);
};

#endif // DATAVIEWUTILS_H