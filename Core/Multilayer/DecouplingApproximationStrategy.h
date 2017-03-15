// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DecouplingApproximationStrategy.h
//! @brief     Defines class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECOUPLINGAPPROXIMATIONSTRATEGY_H
#define DECOUPLINGAPPROXIMATIONSTRATEGY_H

#include "IInterferenceFunctionStrategy.h"

class SimulationElement;

//! Strategy class to compute the total scattering from a particle layout
//! in the decoupling approximation.
//! @ingroup algorithms_internal

class DecouplingApproximationStrategy final : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy(SimulationOptions sim_params, bool polarized);

protected:
    double evaluateForList(const SimulationElement& sim_element) const override;

private:
    double scalarCalculation(const SimulationElement& sim_element) const;
    double polarizedCalculation(const SimulationElement& sim_element) const;
    bool m_polarized;
};

#endif // DECOUPLINGAPPROXIMATIONSTRATEGY_H
