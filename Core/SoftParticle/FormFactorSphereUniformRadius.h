// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereUniformRadius.h
//! @brief     Declares class FormFactorSphereUniformRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEREUNIFORMRADIUS_H
#define FORMFACTORSPHEREUNIFORMRADIUS_H

#include "FormFactorFullSphere.h"

//! @class FormFactorSphereUniformRadius
//! @ingroup formfactors
//! @brief Integrated full sphere form factor over a uniform distribution of radii.

class BA_CORE_API_ FormFactorSphereUniformRadius : public IFormFactorBorn
{
public:
    FormFactorSphereUniformRadius(double mean, double full_width);

    FormFactorSphereUniformRadius *clone() const {
        return new FormFactorSphereUniformRadius(m_mean, m_full_width); }
    void accept(ISampleVisitor *visitor) const final { visitor->visit(this); }

    double getRadialExtension() const final { return m_mean; }

    complex_t evaluate_for_q(const cvector_t q) const final;

private:
    bool checkParameters() const;
    double m_mean; //!< This is the mean radius
    double m_full_width; //!< This is the full width of the radius distribution
};

#endif // FORMFACTORSPHEREUNIFORMRADIUS_H
