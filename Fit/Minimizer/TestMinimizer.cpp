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
#include "Parameters.h"
#include <sstream>

using namespace Fit;

std::string TestMinimizer::minimizerName() const
{
    return std::string(MinimizerNames::Test);
}

//! run minimization
void TestMinimizer::minimize()
{
    m_min_value = m_fcn(m_parameter_values);
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

MinimizerResult TestMinimizer::minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters)
{
    // calling user function once
    auto min_value = fcn(parameters);

    MinimizerResult result;
    result.setParameters(parameters);
    result.setMinValue(min_value);

    std::ostringstream report;
    report << "TestMinimizer::printOutcome() -> Done. Objective function value = "
           << min_value << std::endl;

    result.setReport(report.str());
    result.setNumberOfCalls(1);

    return result;
}
