// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerUtils.h
//! @brief     Defines helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYERUTILS_H
#define MULTILAYERUTILS_H

#include "Complex.h"
#include "WinDllMacros.h"
#include <cstddef>
#include <vector>

class Layer;
class LayerInterface;
class LayerRoughness;
class MultiLayer;
class ZLimits;

namespace MultiLayerUtils
{
//! Returns thickness of layer
BA_CORE_API_ double LayerThickness(const MultiLayer& multilayer, size_t i);

//! Returns top interface of layer
BA_CORE_API_ const LayerInterface* LayerTopInterface(const MultiLayer& multilayer, size_t i);

//! Returns bottom interface of layer
BA_CORE_API_ const LayerInterface* LayerBottomInterface(const MultiLayer& multilayer, size_t i);

//! Returns top roughness of layer
BA_CORE_API_ const LayerRoughness* LayerTopRoughness(const MultiLayer& multilayer, size_t i);

//! Returns the index of the given layer
BA_CORE_API_ size_t IndexOfLayer(const MultiLayer& multilayer, const Layer* p_layer);

//! Returns true if the multilayer contains non-default materials of one type only
BA_CORE_API_ bool ContainsCompatibleMaterials(const MultiLayer& multilayer);

//! Calculate z-regions occupied by particles
BA_CORE_API_ std::vector<ZLimits> ParticleRegions(const MultiLayer& multilayer, bool use_slicing);

//! Calculate average material profile for given multilayer
BA_CORE_API_ std::vector<complex_t> MaterialProfile(const MultiLayer& multilayer, int n_points,
                                                    double z_min, double z_max);
} // namespace MultiLayerUtils

#endif // MULTILAYERUTILS_H
