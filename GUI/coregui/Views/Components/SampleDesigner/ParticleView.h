// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/ParticleView.h
//! @brief     Defines class ParticleView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEVIEW_H
#define PARTICLEVIEW_H


#include "ConnectableView.h"
#include <QPixmap>

//! Class representing view of Particle item
class BA_CORE_API_ ParticleView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::PARTICLE };

    ParticleView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setParameterizedItem(ParameterizedItem *item);

    void onPropertyChange(const QString &propertyName);

    void addView(IView *childView, int row = 0); // to add Transformation

private:
    QPixmap m_pixmap;

};



#endif
