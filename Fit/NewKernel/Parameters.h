// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Parameters.h
//! @brief     Defines class Parameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "WinDllMacros.h"
#include "Parameter.h"
#include <vector>

namespace Fit {

//! A collection of fit parameters.
//! @ingroup fitting

class BA_CORE_API_ Parameters
{
public:
    using parameters_t = std::vector<Parameter>;
    using const_iterator = parameters_t::const_iterator;
    using iterator = parameters_t::iterator;

    Parameters() = default;

    void add(const Parameter& par);

    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    size_t size() const;

private:
    bool exists(const std::string& parameter_name) const;

    parameters_t m_parameters;
};

}  // namespace Fit

#endif  // PARAMETERS_H
