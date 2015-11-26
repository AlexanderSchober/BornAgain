// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskDrawingContext.h
//! @brief     Defines class MaskDrawingContext
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKDRAWINGCONTEXT_H
#define MASKDRAWINGCONTEXT_H

#include "WinDllMacros.h"
#include "MaskEditorFlags.h"

//! Helper class for MaskGraphicsScene to hold drawing conditions

class BA_CORE_API_ MaskDrawingContext
{
public:
    MaskDrawingContext();

    MaskEditorFlags::Activity getActivityType() const;
    void setActivityType(MaskEditorFlags::Activity value);
    void setMaskValue(MaskEditorFlags::MaskValue value);

    bool isSelectionMode() const;
    bool isInZoomMode() const;
    bool isRectangleMode() const;
    bool isEllipseMode() const;
    bool isPolygonMode() const;
    bool isLineMode() const;
    bool isVerticalLineMode() const;
    bool isHorizontalLineMode() const;
    bool isMaskAllMode() const;

    bool isDrawingInProgress() const;
    void setDrawingInProgress(bool value);

    bool getMaskValue() const;

private:

    MaskEditorFlags::Activity m_current_activity;
    MaskEditorFlags::MaskValue m_mask_value;
    bool m_drawing_in_progress;
};


#endif
