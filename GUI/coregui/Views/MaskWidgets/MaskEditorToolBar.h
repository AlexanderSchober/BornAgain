// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolBar.h
//! @brief     Defines class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORTOOLBAR_H
#define MASKEDITORTOOLBAR_H

#include "WinDllMacros.h"
#include "MaskEditorFlags.h"
#include <QToolBar>

class MaskEditorActions;
class QButtonGroup;

//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaskEditorToolBar(MaskEditorActions *editorActions, QWidget *parent = 0);

signals:
    void activityModeChanged(MaskEditorFlags::Activity);
    void propertyPanelRequest();
    void showResultsRequest();
    void maskValueChanged(MaskEditorFlags::MaskValue);
    void resetViewRequest();

public slots:
    void onChangeActivityRequest(MaskEditorFlags::Activity value);

private slots:
    void onActivityGroupChange(int value);
    void onMaskValueGroupChange(int value);

private:
    void setup_selection_group();
    void setup_maskvalue_group();
    void setup_shapes_group();
    void setup_maskmodify_group();
    void setup_extratools_group();
    void add_separator();

    MaskEditorFlags::Activity getCurrentActivity() const;
    void setCurrentActivity(MaskEditorFlags::Activity value);

    MaskEditorActions *m_editorActions;
    QButtonGroup *m_activityButtonGroup;
    QButtonGroup *m_maskValueGroup;
    MaskEditorFlags::Activity m_previousActivity;
};


#endif
