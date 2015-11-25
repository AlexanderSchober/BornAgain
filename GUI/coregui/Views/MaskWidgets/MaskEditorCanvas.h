// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorCanvas.h
//! @brief     Defines class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORCANVAS_H
#define MASKEDITORCANVAS_H

#include "MaskEditorFlags.h"
#include <QWidget>

class MaskGraphicsScene;
class MaskGraphicsView;
class MaskGraphicsProxy;
class SessionModel;
class QItemSelectionModel;
class QModelIndex;
class MaskResultsPresenter;
class QStackedWidget;

//! Painting widget for MaskEditor, contains graphics scene and graphics view

class MaskEditorCanvas : public QWidget
{
    Q_OBJECT
public:
    MaskEditorCanvas(QWidget *parent = 0);

    void setModel(SessionModel *model, const QModelIndex &rootIndex);
    void setSelectionModel(QItemSelectionModel *model);

    MaskGraphicsScene *getScene();
    MaskGraphicsView *getView();

public slots:
    void onShowResultsRequest();

private:
    MaskGraphicsScene *m_scene;
    MaskGraphicsView *m_view;
    MaskResultsPresenter *m_resultsPresenter;
    QStackedWidget *m_stack;
};


#endif
