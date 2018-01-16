// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation2D.h
//! @brief     Defines class Simulation2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATION2D_H
#define SIMULATION2D_H

#include "Simulation.h"

//! Pure virtual base class of OffSpecularSimulation and GISASSimulation.
//! Holds the common implementations for simulations with a 2D detector
//! @ingroup simulation

class BA_CORE_API_ Simulation2D : public Simulation
{
public:
    Simulation2D() =default;
    Simulation2D(const MultiLayer& p_sample);
    Simulation2D(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder);
    virtual ~Simulation2D() =default;

    virtual Simulation2D* clone() const =0;
};

#endif // SIMULATION2D_H
