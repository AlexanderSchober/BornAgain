// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTestPlan.h
//! @brief     Implements class MinimizerTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerTestPlan.h"
#include "Parameters.h"
#include "Numeric.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace Fit;

MinimizerTestPlan::MinimizerTestPlan(const std::string& name) : m_name(name)
{
}

MinimizerTestPlan::~MinimizerTestPlan() = default;

void MinimizerTestPlan::addParameter(const Parameter& param, double expected_value, double tolerance)
{
    m_parameter_plan.push_back(ParameterPlan(param, expected_value, tolerance));
}

//! Returns fit parameters which will be used as initial one for the minimization.

Parameters MinimizerTestPlan::parameters() const
{
    Parameters result;
    for (const auto& plan : m_parameter_plan)
        result.add(plan.fitParameter());

    return result;
}

//! Return vector of expected parameter values.

std::vector<double> MinimizerTestPlan::expectedValues() const
{
    std::vector<double> result;
    for (const auto& plan : m_parameter_plan)
        result.push_back(plan.expectedValue());

    return result;
}

//! Returns true if given values coincide with expected fit parameter values.

bool MinimizerTestPlan::valuesAsExpected(const std::vector<double>& values) const
{
    bool success(true);

    if (m_parameter_plan.size() != values.size())
        throw std::runtime_error("FunctionTestPlan::valuesAsExpected() -> Error. Sizes differ.");

    size_t index(0);
    std::ostringstream text;
    for (const auto& plan : m_parameter_plan) {
        double diff = Numeric::get_relative_difference(values[index], plan.expectedValue());
        if (diff > plan.tolerance())
            success = false;

        text << plan.fitParameter().name() << " found:" << values[index]
             << " expected:" << plan.expectedValue() << " diff:" << diff << " "
             << (success ? "OK" : "FAILED") << "\n";

        ++index;
    }

    std::cout << text.str();

    return success;
}
