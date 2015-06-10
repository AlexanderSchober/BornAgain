// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/DistributionDialog.cpp
//! @brief     Implements class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DistributionDialog.h"
#include "DistributionEditor.h"
#include "ParameterizedItem.h"
#include <QHBoxLayout>
#include <QPushButton>

DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent), m_editor(new DistributionEditor)
{
    setMinimumSize(256, 256);
    resize(700, 480);
    setWindowTitle("Select Distribution");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setModal(true);

    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Close", this);
    button->setAutoDefault(false);
    connect(button, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->setContentsMargins(4, 4, 4, 4);
    buttonLayout->addWidget(button);

    layout->addWidget(m_editor);
    layout->addLayout(buttonLayout);

    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void DistributionDialog::setItem(ParameterizedItem *item)
{
    m_editor->setItem(item);
}

void DistributionDialog::setNameOfEditor(const QString &name)
{
    m_editor->setNameOfEditor(name);
}
