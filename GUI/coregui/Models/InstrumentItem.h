// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/InstrumentItem.h
//! @brief     Defines class InstrumentItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENT_ITEM_H
#define INSTRUMENT_ITEM_H


#include "ParameterizedItem.h"
class BeamItem;
class DetectorItem;

class BA_CORE_API_ InstrumentItem : public ParameterizedItem
{
    Q_OBJECT

public:
    explicit InstrumentItem(ParameterizedItem *parent=0);
    ~InstrumentItem(){}

    BeamItem *getBeamItem();

    DetectorItem *getDetectorItem();

};



#endif
