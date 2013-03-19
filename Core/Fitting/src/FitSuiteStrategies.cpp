// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/src/FitSuiteStrategies.cpp
//! @brief     Implements class FitSuiteStrategies.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FitSuiteStrategies.h"
#include "FitSuite.h"
#include <cassert>

FitSuiteStrategies::FitSuiteStrategies() : m_fit_suite(0), m_current_strategy_index(0)
{
}

FitSuiteStrategies::~FitSuiteStrategies()
{
    clear();
}

void FitSuiteStrategies::clear()
{
    m_strategies.clear();
    m_current_strategy_index = 0;
}

void FitSuiteStrategies::addStrategy(IFitSuiteStrategy *strategy)
{
    assert(m_fit_suite);
    strategy->init(m_fit_suite);
    m_strategies.push_back(strategy);
}

void FitSuiteStrategies::minimize()
{
    m_current_strategy_index = 0;
    if( m_strategies.empty() ) {
         m_fit_suite->minimize();
    } else {
        for(strategies_t::iterator it=m_strategies.begin(); it!=m_strategies.end(); ++it) {
            std::cout << "FitSuiteStrategies::minimize() -> Info. Running strategy #" << m_current_strategy_index << " '" << (*it)->getName() << "'" << std::endl;
            (*it)->execute();
            ++m_current_strategy_index;
        }
    }
}
