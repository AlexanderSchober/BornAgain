// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSpheroid.cpp
//! @brief     Implements class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorFullSpheroid.h"
#include "BornAgainNamespace.h"
#include "FormFactorTruncatedSpheroid.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"
#include "TruncatedEllipsoid.h"
#include <limits>

//! Constructor of full spheroid.
//! @param radius: radius of the circular cross section in nanometers
//! @param height: height of the full spheroid in nanometers
FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height)
    : m_radius(radius), m_height(height)
{
    setName(BornAgain::FFFullSpheroidType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    mP_integrator = make_integrator_complex(this, &FormFactorFullSpheroid::Integrand);
    onChange();
}

//! Integrand for complex formfactor.
complex_t FormFactorFullSpheroid::Integrand(double Z) const
{
    double R = m_radius;
    double H = m_height;

    double Rz = R * std::sqrt(1 - 4.0 * Z * Z / (H * H));
    complex_t qxy = std::sqrt(m_q.x() * m_q.x() + m_q.y() * m_q.y());
    complex_t qrRz = qxy * Rz;
    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_J1c(qrRz);

    return Rz * Rz * J1_qrRz_div_qrRz * std::cos(m_q.z() * Z);
}

complex_t FormFactorFullSpheroid::evaluate_for_q(cvector_t q) const
{
    double H = m_height;
    double R = m_radius;
    m_q = q;

    if (std::abs(m_q.mag()) <= std::numeric_limits<double>::epsilon())
        return M_TWOPI * R * R * H / 3.;
    complex_t qzH_half = H / 2 * q.z();
    return 4 * M_PI * mP_integrator->integrate(0.0, H / 2.0) * exp_I(qzH_half);
}

IFormFactor* FormFactorFullSpheroid::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    double flattening = m_height / (2.0 * m_radius);
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorTruncatedSpheroid slicedff(m_radius, m_height - effects.dz_bottom, flattening,
                                         effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorFullSpheroid::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_radius, m_radius, m_height / 2.0, m_height, 0.0));
}
