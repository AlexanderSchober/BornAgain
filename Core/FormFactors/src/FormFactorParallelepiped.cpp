// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorParallelepiped.cpp
//! @brief     Implements class FormFactorParallelepiped.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorParallelepiped.h"
#include "MathFunctions.h"

FormFactorParallelepiped::FormFactorParallelepiped(double length, double height)
: m_length(length),
  m_height(height)
{
    setName("FormFactorParallelepiped");
    init_parameters();
}

FormFactorParallelepiped* FormFactorParallelepiped::clone() const
{
    FormFactorParallelepiped *result =
        new FormFactorParallelepiped(m_length, m_height);
    result->setName(getName());
    return result;
}

complex_t FormFactorParallelepiped::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxLdiv2 = q.x()*m_length/2.0;
    complex_t qyLdiv2 = q.y()*m_length/2.0;
    complex_t qzHdiv2 = q.z()*m_height/2.0;

    complex_t phase_factor = std::exp(complex_t(0.0, 1.0)*qzHdiv2);
    return m_height*m_length*m_length
            *phase_factor*
        MathFunctions::Sinc(qxLdiv2)*
        MathFunctions::Sinc(qyLdiv2)*
        MathFunctions::Sinc(qzHdiv2);
}

void FormFactorParallelepiped::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length);
    registerParameter("height", &m_height);
}


