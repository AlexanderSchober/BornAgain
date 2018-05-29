// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleToolBar.cpp
//! @brief     Implements class SampleToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleToolBar.h"
#include "DesignerView.h"
#include "MaterialItemUtils.h"
#include <QAction>
#include <QButtonGroup>
#include <QComboBox>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QToolButton>

#include <RealSpaceDialog.h>

//! main tool bar on top of SampleView window
SampleToolBar::SampleToolBar(SampleModel *sampleModel, QItemSelectionModel* selectionModel,
                             QWidget *parent)
    : StyledToolBar(parent)
    , m_sampleModel(sampleModel)
    , m_selectionModel(selectionModel)
    , m_dialog(nullptr)
    , m_dialog_on(false)
{
    // Select & Pan
    QToolButton *selectionPointerButton = new QToolButton;
    selectionPointerButton->setCheckable(true);
    selectionPointerButton->setChecked(true);
    selectionPointerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_pointer.png"));
    selectionPointerButton->setToolTip("Edit mode.");
    QToolButton *handPointerButton = new QToolButton;
    handPointerButton->setCheckable(true);
    handPointerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_hand.png"));
    handPointerButton->setToolTip("Pan mode (space).");

    m_pointerModeGroup = new QButtonGroup(this);
    m_pointerModeGroup->addButton(selectionPointerButton, DesignerView::RUBBER_SELECTION);
    m_pointerModeGroup->addButton(handPointerButton, DesignerView::HAND_DRAG);
    connect(m_pointerModeGroup, SIGNAL(buttonClicked(int)),
            this, SIGNAL(selectionMode(int)));
    addWidget(selectionPointerButton);
    addWidget(handPointerButton);

    addStyledSeparator();

    // unddo redo
    QToolButton *unddoButton = new QToolButton;
    unddoButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_unddo.png"));
    unddoButton->setToolTip("Unddo last action (not implemented yet).");
    addWidget(unddoButton);
    QToolButton *redoButton = new QToolButton;
    redoButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_redo.png"));
    redoButton->setToolTip("Do again the last undone action (not implemented yet).");
    addWidget(redoButton);

    addStyledSeparator();

    // Remove item
    m_removeButton = new QToolButton;
    m_removeButton->setText("Remove item");
    m_removeButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_removeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeButton->setToolTip("Remove selected items and they child items (del).");
    connect(m_removeButton, SIGNAL(clicked()), this, SIGNAL(deleteItems()));
    addWidget(m_removeButton);

    addStyledSeparator();

    // Center view

    m_centerViewButton = new QToolButton;
    m_centerViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_center.png"));
    m_centerViewButton->setToolTip("Center view.");
    addWidget(m_centerViewButton);
    connect(m_centerViewButton, SIGNAL(clicked()), this, SIGNAL(centerView()));

    // align sample
    m_alignItemsButton = new QToolButton;
    m_alignItemsButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_align.png"));
    m_alignItemsButton->setToolTip("Try to align items.");
    connect(m_alignItemsButton, SIGNAL(clicked()), this, SIGNAL(smartAlign()));
    addWidget(m_alignItemsButton);

    // Zoom
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" Zoom "));
    m_scaleCombo = new QComboBox;
    QStringList scales;
    scales << "25%"<< "50%" << "75%" << "100%" << "125%" << "150%";
    m_scaleCombo->addItems(scales);
    m_scaleCombo->setCurrentIndex(3);
    connect(m_scaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(onScaleComboChanged(QString)));
    addWidget(m_scaleCombo);


    // MaterialEditor
    addWidget(new QLabel(" "));
    m_materialEditorButton = new QToolButton;
    m_materialEditorButton->setText("Material Editor");
    m_materialEditorButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_materialeditor.png"));
    m_materialEditorButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_materialEditorButton->setToolTip("Open material editor (m).");
    m_materialEditorButton->setShortcut(Qt::Key_M);
    connect(m_materialEditorButton, SIGNAL(clicked()), this, SLOT(onMaterialEditorCall()));
    addWidget(m_materialEditorButton);

    addStyledSeparator();

    // RealSpace 3D Viewer
    addWidget(new QLabel(" "));
    m_RealSpaceViewerButton = new QToolButton;
    m_RealSpaceViewerButton->setText("Real Space Viewer");
    //m_RealSpaceViewerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_materialeditor.png"));
    m_RealSpaceViewerButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_RealSpaceViewerButton->setToolTip("Open real space 3D viewer.");
    connect(m_RealSpaceViewerButton, SIGNAL(clicked()), this, SLOT(onRealSpaceViewerCall()));
    addWidget(m_RealSpaceViewerButton);

    // Additional actions
    m_zoomOutAction = new QAction(this);
    m_zoomOutAction->setShortcut(QKeySequence(Qt::Key_Minus));
    connect(m_zoomOutAction, SIGNAL(triggered()), this, SIGNAL(zoomOut()));
    addAction(m_zoomOutAction);

    m_zoomInAction = new QAction(this);
    m_zoomInAction->setShortcut(QKeySequence(Qt::Key_Equal));
    connect(m_zoomInAction, SIGNAL(triggered()), this, SIGNAL(zoomIn()));
    addAction(m_zoomInAction);
}

void SampleToolBar::onViewSelectionMode(int mode)
{
    if(mode == DesignerView::RUBBER_SELECTION || mode == DesignerView::HAND_DRAG)
        m_pointerModeGroup->button(mode)->setChecked(true);
}

void SampleToolBar::onScaleComboChanged(const QString &scale_string)
{
    double scale = scale_string.left(scale_string.indexOf("%")).toDouble() / 100.0;
    emit changeScale(scale);
}

void SampleToolBar::onMaterialEditorCall()
{
    ExternalProperty mp = MaterialItemUtils::selectMaterialProperty();
}

void SampleToolBar::onRealSpaceViewerCall()
{
    // keep only one instance of dialog alive using a boolean flag
    if(!m_dialog_on)
    {
        m_dialog_on = true;
        m_dialog = new RealSpaceDialog(m_sampleModel, m_selectionModel, this);
        m_dialog->show();

        // undo the flag when the dialog is destroyed on close event
        connect(m_dialog, &QAction::destroyed, this, [&](){m_dialog_on = false;} );
    }
}
