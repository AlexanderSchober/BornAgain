// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitStrategyAdjustMinimizer.cpp
//! @brief     Implements class FitStrategyAdjustMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitStrategyAdjustMinimizer.h"
#include "FitKernel.h"
#include "MinimizerFactory.h"


FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer()
    : IFitStrategy("FitStrategyAdjustMinimizer"), m_minimizer(0)
{

}

FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer(const std::string &minimizer_name,
                                                       const std::string &algorithm_name,
                                                       const std::string &minimizer_options)
    : IFitStrategy("FitStrategyAdjustMinimizer"), m_minimizer(0)
{
    setMinimizer(minimizer_name, algorithm_name, minimizer_options);
}

FitStrategyAdjustMinimizer::~FitStrategyAdjustMinimizer()
{
    delete m_minimizer;
}

// partial clone
FitStrategyAdjustMinimizer *FitStrategyAdjustMinimizer::clone() const
{
    FitStrategyAdjustMinimizer *result = new FitStrategyAdjustMinimizer();
    result->setName(getName());
    result->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer));
    return result;
}

IMinimizer *FitStrategyAdjustMinimizer::getMinimizer()
{
    return m_minimizer;
}

void FitStrategyAdjustMinimizer::setMinimizer(IMinimizer *minimizer)
{
    m_minimizer = minimizer;
}

void FitStrategyAdjustMinimizer::setMinimizer(const std::string &minimizer_name,
                                              const std::string &algorithm_name,
                                              const std::string &minimizer_options)
{
    setMinimizer(MinimizerFactory::createMinimizer(minimizer_name, algorithm_name,
                                                              minimizer_options));
}

void FitStrategyAdjustMinimizer::execute()
{

    m_fit_kernel->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer) );

    m_fit_kernel->minimize();

    //m_fit_suite->printResults();

}

MinimizerOptions *FitStrategyAdjustMinimizer::getMinimizerOptions()
{
    if(!m_minimizer) {
        return 0;
    } else {
        return m_minimizer->getOptions();
    }
}

