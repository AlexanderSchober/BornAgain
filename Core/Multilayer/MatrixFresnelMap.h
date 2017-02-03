// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.h
//! @brief     Defines class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATRIXFRESNELMAP_H
#define MATRIXFRESNELMAP_H

#include "IFresnelMap.h"
#include <cstddef>

class ILayerRTCoefficients;
class MultiLayer;
class SimulationElement;

//! Implementation of IFresnelMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixFresnelMap : public IFresnelMap
{
public:
    MatrixFresnelMap(const MultiLayer* p_multilayer, const MultiLayer* p_inverted_multilayer);
    ~MatrixFresnelMap() final {}

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getOutCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const final override;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const final override;

private:
    const MultiLayer* mp_multilayer;
    const MultiLayer* mp_inverted_multilayer;
};

#endif // MATRIXFRESNELMAP_H
