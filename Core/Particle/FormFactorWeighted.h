// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorWeighted.h
//! @brief     Defines class FormFactorWeighted.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORWEIGHTED_H
#define FORMFACTORWEIGHTED_H

#include "IFormFactor.h"

//! Coherent sum of different scalar IFormFactor's with different weights.
//!
//! Used by ParticleComposition and ParticleCoreShell.
//! If same particles are at different positions, then consider
//! FormFactorDecoratorMultiPositionFactor (restore from commit 0500a26de76).

//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorWeighted final : public IFormFactor
{
public:
    FormFactorWeighted();
    ~FormFactorWeighted() override;

    FormFactorWeighted* clone() const override;

    void accept(ISampleVisitor* visitor) const override { visitor->visit(this); }

    double getRadialExtension() const override;

    void addFormFactor(const IFormFactor& form_factor, double weight=1.0);

    void setAmbientMaterial(const IMaterial& material) override;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

#ifndef SWIG
    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;
#endif

protected:
    std::vector<IFormFactor*> m_form_factors;
    std::vector<double> m_weights;
};

#endif // FORMFACTORWEIGHTED_H
