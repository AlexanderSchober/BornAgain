// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/AdjustingScrollArea.cpp
//! @brief     Implements class AdjustingScrollArea
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AdjustingScrollArea.h"
#include <QScrollBar>
#include <QEvent>

AdjustingScrollArea::AdjustingScrollArea(QWidget* parent) : QScrollArea(parent)
{
    setObjectName("MyScrollArea");
    setContentsMargins( 0, 0, 0, 0 );
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("QScrollArea#MyScrollArea {border: 0px; background-color:transparent;}");
}

void AdjustingScrollArea::setWidget(QWidget* w)
{
    QScrollArea::setWidget(w);
    w->installEventFilter(this);
}

QSize AdjustingScrollArea::sizeHint() const
{
    QScrollBar* horizontal = horizontalScrollBar();
    QSize result(viewport()->width(), widget()->height() + horizontal->height() * 2);
    return result;
}

bool AdjustingScrollArea::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == widget() && ev->type() != QEvent::Resize) {
        widget()->setMaximumWidth(viewport()->width());
        setMaximumHeight(height() - viewport()->height() + widget()->height());
    }

    return QScrollArea::eventFilter(obj, ev);
}
