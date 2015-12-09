// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorMaskDelegate.h
//! @brief     Defines class DetectorMaskDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTORMASKDELEGATE_H
#define DETECTORMASKDELEGATE_H

#include "WinDllMacros.h"
#include <QObject>
#include <QModelIndex>

template <class T> class OutputData;

class MaskModel;
class DetectorItem;

//! The DetectorMaskDelegate class provides syncronization between DetectorItem (defined
//! in InstrumentModel) and temporary IntensityDataItem (defined in temporary SessionModel).
//! The later one is used by MaskEditor for mask drawing.

class BA_CORE_API_ DetectorMaskDelegate : public QObject
{
    Q_OBJECT
public:
    DetectorMaskDelegate(QObject *parent);

    void setDetectorItem(DetectorItem *detectorItem);

    MaskModel *getMaskModel();

private:
    void init_mask_model();
    OutputData<double> *createOutputData(DetectorItem *detectorItem);

    MaskModel *m_maskModel;
    QModelIndex m_intensityItemIndex;

    DetectorItem *m_detectorItem;
};


#endif

