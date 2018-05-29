// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandardFitsFactory.h
//! @brief     Defines class StandardFitsFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef STANDARDFITSFACTORY_H
#define STANDARDFITSFACTORY_H

#include "FunctionalTestFactory.h"

//! @class StandardFitsFactory
//! @ingroup standard_samples
//! @brief Factory to create predefined functional fit tests

class StandardFitsFactory : public FunctionalTestFactory
{
public:
    StandardFitsFactory();
};

#endif // STANDARDFITSFACTORY_H
