// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/ThreadInfo.h
//! @brief     Defines struct ThreadInfo.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef THREADINFO_H_
#define THREADINFO_H_

//- -------------------------------------------------------------------
//! @class ThreadInfo
//! @brief Structure holding information for threads
//- -------------------------------------------------------------------
struct ThreadInfo
{
    ThreadInfo();
    size_t n_threads;
    size_t i_thread;
};

inline ThreadInfo::ThreadInfo()
: n_threads(1)
, i_thread(0)
{
}

#endif /* THREADINFO_H_ */
