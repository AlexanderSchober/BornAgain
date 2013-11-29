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
//#include "Numeric.h"
#include "MemberFunctionIntegrator.h"

FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height )
{
    setName("FormFactorFullSpheroid");
    m_radius = radius;
    m_height = height;
    init_parameters();
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

complex_t FormFactorFullSpheroid::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double R = m_radius;
    //m_q = q;

    complex_t qz = q.z();
    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qzH_half  = qz*H/2.0;
    complex_t iqzH_half = complex_t(0.0, 1.0)*qzH_half;
    complex_t a_part    =  std::exp(iqzH_half);

    /*MemberFunctionIntegrator<FormFactorFullSpheroid>::mem_function p_mf =
       & FormFactorFullSpheroid::FullSpheroidIntegral;
    MemberFunctionIntegrator<FormFactorFullSpheroid> integrator(p_mf,this);*/

    if (std::abs(qx) <= Numeric::double_epsilon
            && std::abs(qy) <= Numeric::double_epsilon
            && std::abs(qz) <= Numeric::double_epsilon)
          {
        return 2.*M_PI*R*R*H/3.;
    }

    else {
        double radial = 0.;//integrator.integrate(0.0, H/2.0, (void *)0);
        return a_part * radial;
    }
}

//! Integrand.

/*double FormFactorFullSpheroid::FullSpheroidIntegral(
    double Z, void* params) const
{
    (void)params;

    double R = m_radius;
    double H = m_height;
    m_q = q;
    complex_t qz = m_q.z();
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();

    double Rz  = std::abs(R* std::sqrt(1-((4*Z*Z)/(H*H))));
    double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);

    double J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ?
        MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz :
        0.5;
    return 4.0* M_PI *Rz*Rz* J1_qrRz_div_qrRz * std::cos(qz.real()*Z);*/
//}


