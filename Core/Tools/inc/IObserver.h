// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IObserver.h
//! @brief     Defines classes IObserver and IObservable (Observer pattern).
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "Exceptions.h"
#include <list>
#include <boost/shared_ptr.hpp>


class IObservable;

//! @class IObserver
//! @ingroup tools_internal
//! @brief Observer interface from %Observer pattern, for 1:n object dependencies.

class BA_CORE_API_ IObserver {
public:
    virtual ~IObserver() {}

    //! method which is used by observable subject to notify change in status
    virtual void update (IObservable* /*subject*/) {
        throw NotImplementedException("IObserver::update() -> Not implemented");
    }

};

//! @class IObservable
//! @ingroup tools_internal
//! @brief Observable interface from %Observer pattern, for 1:n object dependencies.

class BA_CORE_API_ IObservable {
public:
    typedef boost::shared_ptr<IObserver > observer_t;
    typedef std::list<observer_t > observerlist_t;

    virtual ~IObservable(){}

    //! attach observer to the list of observers
    virtual void attachObserver(observer_t obj);

    //! notify observers about change in status
    virtual void notifyObservers();

private:
    observerlist_t m_observers;
};

#endif // IOBSERVER_H


