// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/NodeEditorPort.cpp
//! @brief     Implements class NodeEditorPort
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "NodeEditorPort.h"
#include "NodeEditorConnection.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

NodeEditorPort::NodeEditorPort(QGraphicsItem *parent, const QString &name,
                               NodeEditorPort::EPortDirection direction,
                               NodeEditorPort::EPortType port_type)
    : QGraphicsPathItem(parent), m_name(name), m_direction(direction), m_port_type(port_type),
      m_radius(5), m_margin(2)
{
    m_color = getPortTypeColor(port_type);

    QPainterPath p;
    p.addEllipse(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
    setPath(p);

    setPen(QPen(m_color.darker(180)));
    setBrush(m_color);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    if (!m_name.isEmpty()) {
        QGraphicsTextItem *label = new QGraphicsTextItem(this);
        label->setPlainText(m_name);
        QFont serifFont("Monospace", DesignerHelper::getPortFontSize(), QFont::Normal);
        label->setFont(serifFont);

        if (isOutput()) {
            label->setPos(-m_radius - m_margin - label->boundingRect().width(),
                          -label->boundingRect().height() / 2);
        } else {
            label->setPos(m_radius + m_margin, -label->boundingRect().height() / 2);
        }
    }
}

NodeEditorPort::~NodeEditorPort()
{
    QVector<NodeEditorConnection *> connections = m_connections;
    foreach (NodeEditorConnection *conn, connections) {
        conn->setSelected(false);
        delete conn;
    }
}

bool NodeEditorPort::isOutput()
{
    return (m_direction == OUTPUT ? true : false);
}

bool NodeEditorPort::isInput()
{
    return !isOutput();
}

void NodeEditorPort::remove(NodeEditorConnection *connection)
{
    if(m_connections.contains(connection))
        m_connections.remove(m_connections.indexOf(connection));
}

void NodeEditorPort::append(NodeEditorConnection *connection)
{
   m_connections.append(connection);
}

bool NodeEditorPort::isConnected(NodeEditorPort *other)
{
    foreach (NodeEditorConnection *conn, m_connections)
        if (conn->port1() == other || conn->port2() == other)
            return true;

    return false;
}

QColor NodeEditorPort::getPortTypeColor(NodeEditorPort::EPortType port_type)
{
    switch (port_type) {
    case DEFAULT:
        return QColor(Qt::gray);
        break;
    case INTERFERENCE:
        return QColor(Qt::yellow);
        break;
    case PARTICLE_LAYOUT:
        return QColor(Qt::green);
        break;
    case FORM_FACTOR:
        return QColor(Qt::blue);
        break;
    case TRANSFORMATION:
        return QColor(Qt::magenta);
        break;
    default:
        return QColor(Qt::red);
        break;
    }
}

QVariant NodeEditorPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged) {
        foreach (NodeEditorConnection *conn, m_connections) {
            conn->updatePosFromPorts();
            conn->updatePath();
        }
    }
    return value;
}
