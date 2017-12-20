// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.h
//! @brief     Defines class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARMATRIX_H
#define SPECULARMATRIX_H

#include "ScalarRTCoefficients.h"
#include "Vectors3D.h"
#include <vector>

//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//! @ingroup algorithms_internal

class BA_CORE_API_ SpecularMatrix
{
public:
    //! Computes refraction angles and transmission/reflection coefficients
    //! for given coherent wave propagation in a multilayer.
    static void execute(const class MultiLayer& sample, const kvector_t k,
                        std::vector<ScalarRTCoefficients>& coeff);
};

#endif // SPECULARMATRIX_H
