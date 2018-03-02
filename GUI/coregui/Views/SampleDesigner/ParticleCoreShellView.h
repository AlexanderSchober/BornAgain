// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleCoreShellView.h
//! @brief     Defines class ParticleCoreShellView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARTICLECORESHELLVIEW_H
#define PARTICLECORESHELLVIEW_H

#include "ConnectableView.h"

//! Class representing view of Particle item
class BA_CORE_API_ ParticleCoreShellView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::PARTICLE };

    ParticleCoreShellView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void addView(IView *childView, int row = 0);

};


#endif // PARTICLECORESHELLVIEW_H

