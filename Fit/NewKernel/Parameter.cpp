// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Parameter.cpp
//! @brief     Implements class Parameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Parameter.h"

using namespace Fit;

Parameter::Parameter()
    : m_start_value(0.0)
    , m_value(0.0)
    , m_step(0.0)
    , m_error(0.0)
{

}

Parameter::Parameter(const std::string &name, double value, const AttLimits &limits, double step)
    : m_name(name)
    , m_start_value(value)
    , m_value(value)
    , m_step(step)
    , m_error(0.0)
    , m_limits(limits)
{

}

std::string Parameter::name() const
{
    return m_name;
}

AttLimits Parameter::limits() const
{
    return m_limits;
}

double Parameter::value() const
{
    return m_value;
}

double Parameter::step() const
{
    return m_step;
}
