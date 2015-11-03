// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "TestView.h"
#include "MaskEditor.h"
#include <QVBoxLayout>

TestView::TestView(QWidget *parent)
    : QWidget(parent)
{
    MaskEditor *maskEditor = new MaskEditor(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(maskEditor);
    setLayout(layout);
}
