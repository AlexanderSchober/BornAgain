// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongRipple1Lorentz.h
//! @brief     Defines class FormFactorLongRipple1Lorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORLONGRIPPLE1LORENTZ_H
#define FORMFACTORLONGRIPPLE1LORENTZ_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

//! The formfactor for a cosine ripple.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorLongRipple1Lorentz : public IFormFactorBorn
{
public:
    //! @brief FormFactorLongRipple1Lorentz constructor
    //! @param length of Ripple1
    //! @param width of cosine cross section
    //! @param height of cosine cross section
    FormFactorLongRipple1Lorentz(double length, double width, double height);

    FormFactorLongRipple1Lorentz* clone() const override final {
        return new FormFactorLongRipple1Lorentz(m_length, m_width, m_height); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final;

    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getLength() const { return m_length; }

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
    std::unique_ptr<IntegratorComplex<FormFactorLongRipple1Lorentz>> mP_integrator;
#endif
};

#endif // FORMFACTORLONGRIPPLE1LORENTZ_H
