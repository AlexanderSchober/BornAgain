// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/IObserver.cpp
//! @brief     Implements class IObserver, mostly by including IObserver.h.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "IObserver.h"

void IObservable::attachObserver(observer_t obj)
{
    m_observers.push_back(obj);
}

void IObservable::notifyObservers()
{
    for(observerlist_t::iterator it = m_observers.begin(); it!=m_observers.end(); ++it) {
        (*it)->update(this);
    }
}
