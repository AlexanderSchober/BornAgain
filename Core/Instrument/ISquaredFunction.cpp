// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISquaredFunction.cpp
//! @brief     Implements classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ISquaredFunction.h"
#include <algorithm>

IVarianceFunction::IVarianceFunction() = default;
IVarianceFunction::~IVarianceFunction() = default;

VarianceDefaultFunction* VarianceDefaultFunction::clone() const
{
    return new VarianceDefaultFunction();
}

double VarianceDefaultFunction::variance(double, double) const
{
    return 1.0;
}

VarianceSimFunction::VarianceSimFunction(double epsilon) : m_epsilon(epsilon)
{
}

VarianceSimFunction* VarianceSimFunction::clone() const
{
    return new VarianceSimFunction(m_epsilon);
}

double VarianceSimFunction::variance(double /*exp*/, double sim) const
{
    return std::max(sim, m_epsilon);
}
