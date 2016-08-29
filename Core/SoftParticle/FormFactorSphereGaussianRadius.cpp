// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereGaussianRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorSphereGaussianRadius.h"
#include "BornAgainNamespace.h"
#include "Limits.h"
#include "RealParameter.h"

using namespace BornAgain;

FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
: m_mean(mean)
, m_sigma(sigma)
, m_mean_r3(0.0)
, p_ff_sphere(0)
{
    setName(FormFactorSphereGaussianRadiusType);
    m_mean_r3 = calculateMeanR3();
    p_ff_sphere = new FormFactorFullSphere(m_mean_r3);
    registerParameter(BornAgain::MeanRadius, &m_mean).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::SigmaRadius, &m_sigma).setUnit("nm").setNonnegative();
}

FormFactorSphereGaussianRadius::~FormFactorSphereGaussianRadius()
{
    delete p_ff_sphere;
}

complex_t FormFactorSphereGaussianRadius::evaluate_for_q(const cvector_t q) const
{
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double dw = std::exp(-q2*m_sigma*m_sigma/2.0);
    return dw*p_ff_sphere->evaluate_for_q(q);
}

double FormFactorSphereGaussianRadius::calculateMeanR3() const
{
    return std::pow(m_mean*(m_mean*m_mean+3.0*m_sigma*m_sigma),1.0/3.0);
}