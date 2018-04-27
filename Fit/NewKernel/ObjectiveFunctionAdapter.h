// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootObjectiveFuncAdapter.h
//! @brief     Declares class RootObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OBJECTIVEFUNCTIONADAPTER_H
#define OBJECTIVEFUNCTIONADAPTER_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include <memory>

class RootObjectiveFunction;

namespace Fit {

class IFunctionAdapter;
class Parameters;

//! Converts user objective function to function ROOT expects.
//! Handles time of life of function objects.

class ObjectiveFunctionAdapter {
public:
    ObjectiveFunctionAdapter();
    ~ObjectiveFunctionAdapter();

    const RootObjectiveFunction* rootObjectiveFunction(fcn_scalar_t fcn,
                                                       const Parameters& parameters);

private:
    std::unique_ptr<IFunctionAdapter> m_adapter;
};

}  // namespace Fit


#endif  //  OBJECTIVEFUNCTIONADAPTER_H
