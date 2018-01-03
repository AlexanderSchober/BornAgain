// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagnetic.h
//! @brief     Defines class SpecularMagnetic.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARMAGNETIC_H
#define SPECULARMAGNETIC_H

#include "MatrixRTCoefficients.h"
#include "Vectors3D.h"
#include <vector>

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! @ingroup algorithms_internal

class BA_CORE_API_ SpecularMagnetic
{
public:
    //! Computes refraction angle reflection/transmission coefficients
    //! for given multilayer and wavevector k
    static void execute(const class MultiLayer& sample, const kvector_t k,
                        std::vector<MatrixRTCoefficients>& coeff);

private:
    static void calculateEigenvalues(const class MultiLayer& sample, const kvector_t k,
                                     std::vector<MatrixRTCoefficients>& coeff);
    static void calculateTransferAndBoundary(const MultiLayer& sample, const kvector_t k,
                                             std::vector<MatrixRTCoefficients>& coeff);
    static void setForNoTransmission(std::vector<MatrixRTCoefficients>& coeff);
    static complex_t getImExponential(complex_t exponent);
};

#endif // SPECULARMAGNETIC_H
