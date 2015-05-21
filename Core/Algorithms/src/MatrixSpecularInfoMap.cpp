// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/ScalarSpecularInfoMap.cpp
//! @brief     Implements class ScalarSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MatrixSpecularInfoMap.h"
#include "SpecularMagnetic.h"

#include <boost/scoped_ptr.hpp>

MatrixSpecularInfoMap::MatrixSpecularInfoMap(const MultiLayer *multilayer, int layer)
    : m_layer(layer)
{
    if (multilayer){
        mP_multilayer.reset((multilayer->clone()));
        mP_inverted_multilayer.reset(multilayer->cloneInvertB());
    }
}

MatrixSpecularInfoMap *MatrixSpecularInfoMap::clone() const
{
    MatrixSpecularInfoMap *result = new MatrixSpecularInfoMap(0, m_layer);
    if (mP_multilayer.get()){
        result->mP_multilayer.reset(mP_multilayer->clone());
        result->mP_inverted_multilayer.reset(mP_inverted_multilayer->clone());
    }
    return result;
}

const MatrixRTCoefficients *MatrixSpecularInfoMap::getOutCoefficients(
        double alpha_f, double phi_f, double wavelength) const
{
    SpecularMagnetic specular_calculator;
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    kvector_t kvec;
    // phi has no effect on R,T, so just pass zero:
    kvec.setLambdaAlphaPhi(wavelength, alpha_f, phi_f);
    specular_calculator.execute(*mP_inverted_multilayer, -kvec, coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer]);
}

const MatrixRTCoefficients *MatrixSpecularInfoMap::getInCoefficients(
        double alpha_i, double phi_i, double wavelength) const
{
    SpecularMagnetic specular_calculator;
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    kvector_t kvec;
    // phi has no effect on R,T, so just pass zero:
    kvec.setLambdaAlphaPhi(wavelength, alpha_i, phi_i);
    specular_calculator.execute(*mP_multilayer, kvec, coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer]);
}
