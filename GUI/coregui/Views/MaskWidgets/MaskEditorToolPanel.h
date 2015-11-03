// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolPanel.h
//! @brief     Defines class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORTOOLPANEL_H
#define MASKEDITORTOOLPANEL_H

#include <QWidget>

//! Tool widget for MaskEditor

class MaskEditorToolPanel : public QWidget
{
    Q_OBJECT
public:
    MaskEditorToolPanel(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(128, 128); }
    QSize minimumSizeHint() const { return QSize(128, 128); }


};


#endif
