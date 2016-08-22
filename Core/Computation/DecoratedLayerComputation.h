// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DecoratedLayerComputation.h
//! @brief     Defines class DecoratedLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECORATEDLAYERCOMPUTATION_H
#define DECORATEDLAYERCOMPUTATION_H

#include "Computation.h"

class IInterferenceFunctionStrategy;
class Layer;
class LayerSpecularInfo;

//! Computes the scattering contribution from one layer with particles in/on it.
//! Controlled by MainComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ DecoratedLayerComputation : public Computation
{
public:
    DecoratedLayerComputation(const Layer* p_layer, size_t layout_index=0);
    ~DecoratedLayerComputation() final;

    void run() final;
    void setSpecularInfo(const LayerSpecularInfo& specular_info);

private:
    void runProtected() final;
    IInterferenceFunctionStrategy* createAndInitStrategy() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy* p_strategy);

    Layer* mp_layer;
    LayerSpecularInfo* mp_specular_info;
    size_t m_layout_index;
};

#endif // DECORATEDLAYERCOMPUTATION_H
