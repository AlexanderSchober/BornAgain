// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PyScriptFunctionalTestComponentService.cpp
//! @brief     Implements class PyScriptFunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyScriptFunctionalTestComponentService.h"
#include "PyScriptFunctionalTest.h"

PyScriptFunctionalTestComponentService::PyScriptFunctionalTestComponentService(
    const FunctionalTestInfo &info)
    : FunctionalTestComponentService(info)
{
}

IFunctionalTest *PyScriptFunctionalTestComponentService::getFunctionalTest() const
{
    PyScriptFunctionalTest *result = new PyScriptFunctionalTest(getTestName(),
        getTestDescription(), getSimulation(), getTestThreshold());
    return result;
}
