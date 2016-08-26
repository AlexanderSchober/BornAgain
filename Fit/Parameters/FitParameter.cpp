// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameter.cpp
//! @brief     Implements class FitParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameter.h"
#include <iomanip>

FitParameter::FitParameter() : m_value(0), m_step(0), m_error(0)
{}

FitParameter::FitParameter(
    const std::string& name, double value, double step, const RealLimits& limits,
    const Attributes& attr, double error)
    : RealLimits(limits)
    , Attributes(attr)
    , m_name(name)
    , m_value(value)
    , m_step(step)
    , m_error(error)
{}

void FitParameter::print(std::ostream& ostr) const
{
    const int max_length_of_name(40);
    std::string adjusted_name = m_name;
    adjusted_name.resize(max_length_of_name,' ');
    ostr << adjusted_name << std::scientific << std::setprecision(8) << m_value << "  ";
    Attributes::print(ostr);
    ostr << " ";
    RealLimits::print(ostr);
}
