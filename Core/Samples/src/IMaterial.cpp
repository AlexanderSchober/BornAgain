// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/IMaterial.cpp
//! @brief     Implements class IMaterial.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMaterial.h"

Eigen::Matrix2cd IMaterial::getScatteringMatrix(double k_mag2) const
{
    (void)k_mag2;
    return Eigen::Matrix2cd::Identity();
}

