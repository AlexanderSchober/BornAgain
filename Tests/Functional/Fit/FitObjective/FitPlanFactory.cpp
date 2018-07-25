// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlanFactory.cpp
//! @brief     Implements class FitPlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlanFactory.h"
#include "FitPlanCases.h"

FitPlanFactory::FitPlanFactory()
{
    registerItem("CylindersInBAPlan", create_new<CylindersInBAPlan>);
}
