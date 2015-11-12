// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/RectangleView.h
//! @brief     Defines RectangleView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include "IMaskView.h"
#include "SizeHandleElement.h"
#include <QMap>

//! This is a View of rectangular mask ( represented by RectangleItem) on GraphicsScene.
//! Given view follows standard QGraphicsScene notations: (x,y) is top left corner.

class BA_CORE_API_ RectangleView : public IMaskView
{
    Q_OBJECT

public:
    RectangleView();

public slots:
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

private slots:
    void onSizeHandleElementRequest(bool going_to_resize);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void update_view();
    void update_bounding_rect();
    void update_position();    
    qreal left() const;
    qreal right() const;
    qreal width() const;
    qreal top() const;
    qreal bottom() const;
    qreal height() const;
    void create_size_handle_elements();
    bool m_block_on_property_change;
    QRectF m_mask_rect; // mask rectangle in scene coordinates

    QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *> m_resize_handles;
     //!< coordinates of corner opposite to the grip corner at the moment it first clicked
    QPointF m_resize_opposite_origin;
    SizeHandleElement *m_activeHandleElement;
};


#endif
