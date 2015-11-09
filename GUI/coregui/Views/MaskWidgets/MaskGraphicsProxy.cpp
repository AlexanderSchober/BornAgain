// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsProxy.cpp
//! @brief     Implements class MaskGraphicsProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskGraphicsProxy.h"
#include <QGraphicsSceneMouseEvent>
#include "ColorMapPlot.h"
#include "ColorMapSceneAdaptor.h"
#include "IntensityDataItem.h"
#include <QDebug>

MaskGraphicsProxy::MaskGraphicsProxy()
    : m_colorMap(new ColorMapPlot)
    , m_sceneAdaptor(0)
    , m_send_signals_to_colormap(true)
{

}

MaskGraphicsProxy::~MaskGraphicsProxy()
{
    // no need to delete m_colorMap, base QGraphicsProxyWidget will take care about it

    qDebug() << "MaskGraphicsProxy::~MaskGraphicsProxy()";
    if(m_sceneAdaptor) {
        m_sceneAdaptor->setColorMapPlot(0);
    }
}

void MaskGraphicsProxy::setItem(IntensityDataItem *intensityDataItem)
{
    m_colorMap->setItem(intensityDataItem);
    if(widget() != m_colorMap) setWidget(m_colorMap);
}

void MaskGraphicsProxy::setSceneAdaptor(ISceneAdaptor *sceneAdaptor)
{
    m_sceneAdaptor = dynamic_cast<ColorMapSceneAdaptor *>(sceneAdaptor);
    Q_ASSERT(m_sceneAdaptor);
    m_sceneAdaptor->setColorMapPlot(m_colorMap);
}

void MaskGraphicsProxy::setSendSignalsToColormap(bool value)
{
    m_send_signals_to_colormap = value;
}

void MaskGraphicsProxy::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    QGraphicsProxyWidget::mousePressEvent(event);
    event->accept();
}

void MaskGraphicsProxy::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}

void MaskGraphicsProxy::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    qDebug() << "MaskGraphicsProxy::wheelEvent()" << event->pos();
    QGraphicsProxyWidget::wheelEvent(event);
}



void MaskGraphicsProxy::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    qDebug() << "MaskGraphicsProxy::mouseMoveEvent()" << event->pos();
    QGraphicsProxyWidget::mouseMoveEvent(event);
}
