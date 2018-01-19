// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IBackground.cpp
//! @brief     Implements interface IBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IBackground.h"
#include "SimulationElement.h"

IBackground::~IBackground() {}

void IBackground::addBackGround(std::vector<SimulationElement>::iterator start,
                       std::vector<SimulationElement>::iterator end) const
{
    for (auto it = start; it != end; it++)
        addBackGround(*it);
}
