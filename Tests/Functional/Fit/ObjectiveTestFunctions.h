// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ObjectiveTestFunctions.h
//! @brief     Declares set of ObjectiveTestFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OBJECTIVETESTFUNCTIONS_G
#define OBJECTIVETESTFUNCTIONS_G

#include "WinDllMacros.h"
#include <vector>

//! @class StandaloneFitTest
//! @ingroup standard_samples
//! @brief Collection of objective functions for minimization library testing.
//! Borrowed from StressFit test framework of http://root.cern.ch.

namespace TestFunctions
{
double RosenBrock(const std::vector<double>& par);
double WoodFour(const std::vector<double>& par);
}

#endif

