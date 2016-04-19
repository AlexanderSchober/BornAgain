// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/ResolutionFunction2DGaussian.cpp
//! @brief     Implements class ResolutionFunction2DGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ResolutionFunction2DGaussian.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(double sigma_x,
        double sigma_y)
: m_sigma_x(sigma_x)
, m_sigma_y(sigma_y)
{
    setName(BornAgain::ResolutionFunction2D);
    init_parameters();
}

ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(const ResolutionFunction2DGaussian& other) : IResolutionFunction2D(other)
{
    m_sigma_x = other.m_sigma_x;
    m_sigma_y = other.m_sigma_y;
    init_parameters();
}

ResolutionFunction2DGaussian *ResolutionFunction2DGaussian::clone() const
{
    return new ResolutionFunction2DGaussian(*this);
}

double ResolutionFunction2DGaussian::evaluateCDF(double x, double y) const
{
    return MathFunctions::IntegratedGaussian(x, 0.0, m_sigma_x)
                * MathFunctions::IntegratedGaussian(y, 0.0, m_sigma_y);
}

void ResolutionFunction2DGaussian::init_parameters()
{
    clearParameterPool();
    registerParameter(BornAgain::SigmaX, &m_sigma_x);
    registerParameter(BornAgain::SigmaY, &m_sigma_y);
}
