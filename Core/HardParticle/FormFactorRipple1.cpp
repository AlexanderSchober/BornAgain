// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple1.cpp
//! @brief     Implements class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorRipple1.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealLimits.h"
#include "RealParameter.h"
#include "RippleCosine.h"

//! @brief Constructor of cosine ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
FormFactorRipple1::FormFactorRipple1(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFRipple1Type);
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    mP_integrator = make_integrator_complex(this, &FormFactorRipple1::Integrand);
    onChange();
}

bool FormFactorRipple1::check_initialization() const
{
    bool result(true);
    if (m_height <= 0.0 || m_width <= 0.0 || m_length <= 0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorRipple1() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

double FormFactorRipple1::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Integrand for complex formfactor.
complex_t FormFactorRipple1::Integrand(double u) const
{
    return sin(u) * exp(m_az * std::cos(u)) * (m_ay == 0. ? u : sin(m_ay * u) / m_ay);
}

//! Complex formfactor.
complex_t FormFactorRipple1::evaluate_for_q(cvector_t q) const
{
    complex_t factor = m_length * MathFunctions::sinc(q.x() * m_length * 0.5) * m_width / M_PI;

    // analytical expressions for some particular cases
    if (q.z() == 0.) {
        if (q.y() == 0.)
            return factor * M_PI_2 * m_height;
        complex_t aaa = q.y() * m_width / (M_TWOPI);
        complex_t aaa2 = aaa * aaa;
        if (aaa2 == 1.)
            return factor * M_PI_4 * m_height;
        return factor * M_PI_2 * m_height * MathFunctions::sinc(q.y() * m_width * 0.5)
               / (1.0 - aaa2);
    }

    // numerical integration otherwise
    m_ay = q.y() * m_width / M_TWOPI;
    m_az = complex_t(0, 1) * q.z() * (m_height / 2);
    complex_t integral = mP_integrator->integrate(0, M_PI);
    return factor * integral * exp(m_az) * (m_height / 2);
}

void FormFactorRipple1::onChange()
{
    mP_shape.reset(new RippleCosine(m_length, m_width, m_height));
}
