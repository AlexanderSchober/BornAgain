// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitSuitePrintObserver.h
//! @brief     Defines class FitSuitePrintObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEPRINTOBSERVER_H
#define FITSUITEPRINTOBSERVER_H

#include "IObserver.h"
#include <boost/date_time/posix_time/posix_time.hpp>
class FitSuite;

//! @class FitSuitePrintObserver
//! @ingroup fitting_internal
//! @brief Prints fit progress at the end of each FitSuite's iteration

class BA_CORE_API_ FitSuitePrintObserver : public IObserver
{
public:
    FitSuitePrintObserver(int print_every_nth = 1);
    virtual ~FitSuitePrintObserver(){}

    void update(IObservable *subject);

private:
    bool skipIteration();
    void checkStrategy();

    FitSuite *m_fitSuite;
    int m_print_every_nth;
    int m_previous_strategy_index;
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_last_call_time;
    bool m_strategy_is_changed;
};

#endif // FITSUITEPRINTOBSERVER_H


