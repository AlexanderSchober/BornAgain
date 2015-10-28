// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Numeric.h
//! @brief     Defines constants and "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NUMERIC_H_
#define NUMERIC_H_

#include "WinDllMacros.h"
#include <limits>
#include <cmath>
#include <algorithm>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric {

static const double required_precision = 1.e-4;

static const double double_epsilon = std::numeric_limits<double>::epsilon();

static const double double_min = std::numeric_limits<double>::min();

//! threshold on probability value during calculation of weighted form factor
static const double probthreshold = 0.0000000001;

//! compare two doubles
bool BA_CORE_API_ areAlmostEqual(double a, double b, double tolerance_factor=1.0);

//! calculates safe relative difference |(a-b)/b|
double BA_CORE_API_ get_relative_difference(double a, double b);

} // Numeric namespace

#endif /* NUMERIC_H_ */


