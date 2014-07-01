// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleLayoutItem.cpp
//! @brief     Implements class ParticleLayoutItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "ParticleCoreShellItem.h"

ParticleLayoutItem::ParticleLayoutItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("ParticleLayout"), parent)
{
    setItemName(QString("ParticleLayout"));
    setItemPort(ParameterizedItem::PortInfo::Port0);
    addToValidChildren(QString("Particle"), PortInfo::Port0);
    addToValidChildren(ParticleCoreShellItem::P_TYPE_NAME, PortInfo::Port0);
    addToValidChildren(QString("InterferenceFunction1DParaCrystal"), PortInfo::Port1, 1);
    addToValidChildren(QString("InterferenceFunction2DParaCrystal"), PortInfo::Port1, 1);
}


ParticleLayoutItem::~ParticleLayoutItem()
{
}



