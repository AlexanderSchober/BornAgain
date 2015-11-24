// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolBar.cpp
//! @brief     Implements class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorToolBar.h"
#include "MaskEditorActions.h"
#include <QStyle>
#include <QVariant>
#include <QToolButton>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDebug>

namespace {
const int toolbar_icon_size = 32;
}

MaskEditorToolBar::MaskEditorToolBar(MaskEditorActions *editorActions, QWidget *parent)
    : QToolBar(parent)
    , m_editorActions(editorActions)
    , m_activityButtonGroup(new QButtonGroup(this))
    , m_maskValueGroup(new QButtonGroup(this))
{
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    setup_selection_group();
    add_separator();
    setup_maskvalue_group();
    add_separator();
    setup_shapes_group();
    add_separator();
    setup_maskmodify_group();
    add_separator();
    setup_extratools_group();

    connect(m_activityButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(onActivityGroupChange(int)));
    connect(m_maskValueGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(onMaskValueGroupChange(int)));

    m_previousActivity = getCurrentActivity();
}

//! Handles ZOOM requests from MaskGraphicsView while user press and holds
//! space bar. As soon as space bar is released, activity is returned to previous state.
void MaskEditorToolBar::onChangeActivityRequest(MaskEditorFlags::Activity value)
{
    if(value.testFlag(MaskEditorFlags::PAN_ZOOM_MODE)) {
        m_previousActivity = getCurrentActivity();
        m_activityButtonGroup->button(MaskEditorFlags::PAN_ZOOM_MODE)->setChecked(true);
    } else {
        setCurrentActivity(m_previousActivity);
    }
    emit activityModeChanged(getCurrentActivity());
}

void MaskEditorToolBar::onActivityGroupChange(int value)
{
    Q_UNUSED(value);
    emit activityModeChanged(getCurrentActivity());
}

void MaskEditorToolBar::onMaskValueGroupChange(int value)
{
    Q_UNUSED(value);
    emit maskValueChanged(MaskEditorFlags::MaskValue(value));
}

void MaskEditorToolBar::setup_selection_group()
{
    QToolButton *selectionButton = new QToolButton(this);
    selectionButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_arrow.svg"));
    selectionButton->setToolTip("Select/modify mode");
    selectionButton->setCheckable(true);
    selectionButton->setChecked(true);
    addWidget(selectionButton);

    QToolButton *panButton = new QToolButton(this);
    panButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_hand.svg"));
    panButton->setToolTip("Pan/zoom mode (space)");
    panButton->setCheckable(true);
    addWidget(panButton);

    QToolButton *resetViewButton = new QToolButton(this);
    resetViewButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_refresh.svg"));
    resetViewButton->setToolTip("Reset pan/zoom to initial state");
    addWidget(resetViewButton);

    m_activityButtonGroup->addButton(selectionButton, MaskEditorFlags::SELECTION_MODE);
    m_activityButtonGroup->addButton(panButton, MaskEditorFlags::PAN_ZOOM_MODE);

    connect(resetViewButton, SIGNAL(clicked()), this, SIGNAL(resetViewRequest()));
}

void MaskEditorToolBar::setup_maskvalue_group()
{
    addWidget(new QLabel(" "));

    QRadioButton *maskTrueButton = new QRadioButton(this);
    maskTrueButton->setText("masked");
    maskTrueButton->setToolTip("Set mask to True (area is excluded from the simulation)");
    maskTrueButton->setCheckable(true);
    maskTrueButton->setChecked(true);
    addWidget(maskTrueButton);

    addWidget(new QLabel(" "));

    QRadioButton *maskFalseButton = new QRadioButton(this);
    maskFalseButton->setToolTip("Set mask to False (area stays in the simulation)");
    maskFalseButton->setCheckable(true);
    maskFalseButton->setText("active");
    addWidget(maskFalseButton);

    m_maskValueGroup->addButton(maskTrueButton, MaskEditorFlags::MASK_ON);
    m_maskValueGroup->addButton(maskFalseButton, MaskEditorFlags::MASK_OFF);
}

void MaskEditorToolBar::setup_shapes_group()
{
    QToolButton *rectangleButton = new QToolButton(this);
    rectangleButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_rectangle.svg"));
    rectangleButton->setToolTip("Create rectangle mask");
    rectangleButton->setCheckable(true);
    addWidget(rectangleButton);

    QToolButton *polygonButton = new QToolButton(this);
    polygonButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_polygon.svg"));
    polygonButton->setToolTip("Create polygon mask");
    polygonButton->setCheckable(true);
    addWidget(polygonButton);

    QToolButton *verticalLineButton = new QToolButton(this);
    verticalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_verticalline.svg"));
    verticalLineButton->setToolTip("Create vertical line mask");
    verticalLineButton->setCheckable(true);
    addWidget(verticalLineButton);

    QToolButton *horizontalLineButton = new QToolButton(this);
    horizontalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_horizontalline.svg"));
    horizontalLineButton->setToolTip("Create horizontal line mask");
    horizontalLineButton->setCheckable(true);
    addWidget(horizontalLineButton);

    QToolButton *ellipseButton = new QToolButton(this);
    ellipseButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_ellipse.svg"));
    ellipseButton->setToolTip("Create ellipse mask");
    ellipseButton->setCheckable(true);
    addWidget(ellipseButton);

    QToolButton *maskAllButton = new QToolButton(this);
    maskAllButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_maskall.svg"));
    maskAllButton->setToolTip("Create masked area covering whole detector plane\nWill be placed beneath all masks");
    maskAllButton->setCheckable(true);
    addWidget(maskAllButton);

    m_activityButtonGroup->addButton(rectangleButton, MaskEditorFlags::RECTANGLE_MODE);
    m_activityButtonGroup->addButton(polygonButton, MaskEditorFlags::POLYGON_MODE);
    m_activityButtonGroup->addButton(verticalLineButton, MaskEditorFlags::VERTICAL_LINE_MODE);
    m_activityButtonGroup->addButton(horizontalLineButton, MaskEditorFlags::HORIZONTAL_LINE_MODE);
    m_activityButtonGroup->addButton(ellipseButton, MaskEditorFlags::ELLIPSE_MODE);
    m_activityButtonGroup->addButton(maskAllButton, MaskEditorFlags::MASKALL_MODE);
}

void MaskEditorToolBar::setup_maskmodify_group()
{
    Q_ASSERT(m_editorActions);
    addAction(m_editorActions->getBringToFrontAction());
    addAction(m_editorActions->getSendToBackAction());
}

void MaskEditorToolBar::setup_extratools_group()
{
    QToolButton *propertyPanelButton = new QToolButton(this);
    propertyPanelButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_toolpanel.svg"));
    propertyPanelButton->setToolTip("Open panel with additional settings");
    propertyPanelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addWidget(propertyPanelButton);

    connect(propertyPanelButton, SIGNAL(clicked()),
            this, SIGNAL(toolPanelRequest()));
}

void MaskEditorToolBar::add_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

MaskEditorFlags::Activity MaskEditorToolBar::getCurrentActivity() const
{
    MaskEditorFlags::Activity result;
    result |= MaskEditorFlags::EActivityType(m_activityButtonGroup->checkedId());
    qDebug() << "MaskEditorToolBar::getCurrentActivity():" << result;
    return result;
}

void MaskEditorToolBar::setCurrentActivity(MaskEditorFlags::Activity value)
{
    if(value.testFlag(MaskEditorFlags::SELECTION_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::SELECTION_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::PAN_ZOOM_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::PAN_ZOOM_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::RECTANGLE_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::RECTANGLE_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::POLYGON_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::POLYGON_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::VERTICAL_LINE_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::VERTICAL_LINE_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::HORIZONTAL_LINE_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::HORIZONTAL_LINE_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::ELLIPSE_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::ELLIPSE_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorFlags::MASKALL_MODE))
        m_activityButtonGroup->button(MaskEditorFlags::MASKALL_MODE)->setChecked(true);
}

