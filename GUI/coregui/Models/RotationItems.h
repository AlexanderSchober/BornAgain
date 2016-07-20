// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RotationItems.h
//! @brief     Declares class RotationItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ROTATIONITEMS_H
#define ROTATIONITEMS_H

#include "Rotations.h"
#include "SessionItem.h"

class RotationItem : public SessionItem
{

public:
    explicit RotationItem(const QString name) : SessionItem(name){}
    virtual IRotation *createRotation() const{ return 0;}
    virtual ~RotationItem(){}
};


class XRotationItem : public RotationItem
{

public:
    static const QString P_ANGLE;
    explicit XRotationItem();
    IRotation *createRotation() const;
};

class YRotationItem : public RotationItem
{

public:
    static const QString P_ANGLE;
    explicit YRotationItem();
    IRotation *createRotation() const;
};

class ZRotationItem : public RotationItem
{

public:
    static const QString P_ANGLE;
    explicit ZRotationItem();
    IRotation *createRotation() const;
};

class EulerRotationItem : public RotationItem
{

public:
    static const QString P_ALPHA, P_BETA, P_GAMMA;
    explicit EulerRotationItem();
    IRotation *createRotation() const;
};

#endif // ROTATIONITEMS_H

