// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorActions.h
//! @brief     Defines class MaskEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORACTIONS_H
#define MASKEDITORACTIONS_H

#include "WinDllMacros.h"
#include "MaskEditorFlags.h"
#include <QObject>
#include <QModelIndex>

class QAction;
class SessionModel;
class QItemSelectionModel;
class QMenu;
class QMenu;

//! Defines actions for MaskEditor which are related to selected MaskItem (toggle mask value,
//! lower/rize mask in the stack, delete mask). If more than one MaskItem is selected,
//! action will be applied to the whole selection, if possible.

class BA_CORE_API_ MaskEditorActions : public QObject
{
    Q_OBJECT
public:
    MaskEditorActions(QObject *parent);

    void setModel(SessionModel *maskModel, const QModelIndex &rootIndex);
    void setSelectionModel(QItemSelectionModel *selectionModel);

    QAction *getSendToBackAction();
    QAction *getBringToFrontAction();

public slots:
    void onItemContextMenuRequest(const QPoint &point);

private slots:
    void onToggleMaskValueAction();
    void onBringToFrontAction();
    void onSendToBackAction();
    void onDeleteMaskAction();

private:
    void initItemContextMenu(QMenu &menu);
    void changeMaskStackingOrder(MaskEditorFlags::Stacking value);

    QAction *m_toggleMaskValueAction;
    QAction *m_bringToFrontAction;
    QAction *m_sendToBackAction;
    QAction *m_deleteMaskAction;

    SessionModel *m_maskModel;
    QModelIndex m_rootIndex; //! Index in the model corresponding to IntensityDataItem
    QItemSelectionModel *m_selectionModel;
};

#endif
