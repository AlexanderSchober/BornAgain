// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorFullSpheroid.cpp
//! @brief     Implements class FormFactorFullSpheroid.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSpheroid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height )
{
    setName("FormFactorFullSpheroid");
    m_radius = radius;
    m_height = height;
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorFullSpheroid>::mem_function p_mf =
       & FormFactorFullSpheroid::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorFullSpheroid>(p_mf, this);
 }

void FormFactorFullSpheroid::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}

FormFactorFullSpheroid* FormFactorFullSpheroid::clone() const
{
   FormFactorFullSpheroid* result =
       new FormFactorFullSpheroid(m_radius, m_height);
   result->setName(getName());
   return result;
}

//! Integrand for complex formfactor.
complex_t FormFactorFullSpheroid::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    double R = m_radius;
    double H = m_height;

    double Rz  = R*std::sqrt(1-4.0*Z*Z/(H*H));
    complex_t qrRz = m_q.magxy()*Rz;

    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_C1(qrRz);

    return Rz*Rz* J1_qrRz_div_qrRz *std::cos(m_q.z()*Z);
}

complex_t FormFactorFullSpheroid::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double R = m_radius;
    m_q = q;

    if (std::abs(m_q.mag()) <= Numeric::double_epsilon) {

        return 2.*M_PI*R*R*H/3.;

    } else {

        complex_t qzH_half  = m_q.z()*H/2.0;
        complex_t z_part    =  std::exp(complex_t(0.0, 1.0)*qzH_half);

        return 4.0* M_PI * z_part *m_integrator->integrate(0.0, H/2.0);

    }
}




