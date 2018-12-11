// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionFinite3DLattice.h
//! @brief     Defines class InterferenceFunctionFinite3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONFINITE3DLATTICE_H
#define INTERFERENCEFUNCTIONFINITE3DLATTICE_H

#include "IInterferenceFunction.h"
#include "Lattice.h"

//! Interference function of 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionFinite3DLattice : public IInterferenceFunction
{
public:
    InterferenceFunctionFinite3DLattice(const Lattice& lattice, unsigned N_1, unsigned N_2,
                                        unsigned N_3);
    ~InterferenceFunctionFinite3DLattice() final;

    InterferenceFunctionFinite3DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double evaluate(const kvector_t q) const final;

    unsigned numberUnitCells1() const { return m_N_1; }
    unsigned numberUnitCells2() const { return m_N_2; }
    unsigned numberUnitCells3() const { return m_N_3; }

    const Lattice& lattice() const;

    std::vector<const INode*> getChildren() const override;
private:
    InterferenceFunctionFinite3DLattice(const InterferenceFunctionFinite3DLattice& other);
    void setLattice(const Lattice& lattice);

    std::unique_ptr<Lattice> mP_lattice;
    unsigned m_N_1, m_N_2, m_N_3;  //!< Size of the finite lattice in lattice units
};

#endif // INTERFERENCEFUNCTIONFINITE3DLATTICE_H
