// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TestMinimizer.cpp
//! @brief     Implements class TrivialMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TestMinimizer.h"
#include "MinimizerConstants.h"
#include "FitParameterSet.h"
#include <sstream>

std::string TestMinimizer::minimizerName() const
{
    return std::string(MinimizerNames::Test);
}

//! run minimization
void TestMinimizer::minimize()
{
    m_min_value = m_fcn(m_parameter_values);
}

void TestMinimizer::setParameters(const FitParameterSet& parameters)
{
    m_parameter_values = parameters.values();
}

void TestMinimizer::setObjectiveFunction(objective_function_t func)
{
    m_fcn = func;
}

std::string TestMinimizer::reportOutcome() const
{
    std::ostringstream result;
    result << "TestMinimizer::printOutcome() -> Done. Objective function value = "
           << m_min_value << std::endl;
    return result.str();
}

void TestMinimizer::propagateResults(FitParameterSet &)
{
    // nothing to do
}
