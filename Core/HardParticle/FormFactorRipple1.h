// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple1.h
//! @brief     Defines class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE1_H
#define FORMFACTORRIPPLE1_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

//! The formfactor for a cosine ripple.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorRipple1 : public IFormFactorBorn
{
public:
    FormFactorRipple1(double length, double width, double height);

    FormFactorRipple1* clone() const override final {
        return new FormFactorRipple1(m_length, m_width, m_height); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }

    double radialExtension() const override final;

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    void onChange() override final;

private:
    complex_t Integrand(double u) const;
    bool check_initialization() const;

    double m_length;
    double m_width;
    double m_height;

    mutable complex_t m_ay;
    mutable complex_t m_az;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorRipple1>> mP_integrator;
#endif
};

#endif // FORMFACTORRIPPLE1_H
