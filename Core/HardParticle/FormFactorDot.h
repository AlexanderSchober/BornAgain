// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDot.h
//! @brief     Defines class FormFactorDot.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORDOT_H
#define FORMFACTORDOT_H

#include "IFormFactorBorn.h"

//! A dot, with trivial formfactor F(q)=1.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorDot : public IFormFactorBorn
{
public:
    FormFactorDot();

    FormFactorDot* clone() const override final { return new FormFactorDot(); }

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final { return 0; }

    complex_t evaluate_for_q(cvector_t) const override final { return 1; }

protected:
    bool canSliceAnalytically(const IRotation&) const override final { return true; }

    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;
};

#endif // FORMFACTORDOT_H
