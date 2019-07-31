// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.cpp
//! @brief     Implements class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MatrixFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MatrixRTCoefficients.h"
#include "SimulationElement.h"
#include "Slice.h"
#include "SpecularMagnetic.h"

namespace {
std::vector<MatrixRTCoefficients> calculateCoefficients(const std::vector<Slice>& slices,
                                                        kvector_t kvec);

const std::vector<MatrixRTCoefficients>&
getCoefficientsFromCache(kvector_t kvec, const std::vector<Slice>& slices,
                         MatrixFresnelMap::CoefficientHash& hash_table);
}

MatrixFresnelMap::MatrixFresnelMap() = default;

MatrixFresnelMap::~MatrixFresnelMap() = default;

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index, m_inverted_slices,
                           m_hash_table_out);
}

void MatrixFresnelMap::setSlices(const std::vector<Slice> &slices)
{
    IFresnelMap::setSlices(slices);
    m_inverted_slices.clear();
    for (auto slice : slices) {
        slice.invertBField();
        m_inverted_slices.push_back(slice);
    }
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    return getCoefficients(kvec, layer_index, m_slices, m_hash_table_in);
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index,
                                  const std::vector<Slice>& slices, CoefficientHash& hash_table) const
{
    if (!m_use_cache) {
        auto coeffs = calculateCoefficients(slices, kvec);
        return std::make_unique<MatrixRTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec, slices, hash_table);
    return std::make_unique<MatrixRTCoefficients>(coef_vector[layer_index]);
}

namespace {
std::vector<MatrixRTCoefficients> calculateCoefficients(const std::vector<Slice>& slices,
                                                        kvector_t kvec)
{
    std::vector<MatrixRTCoefficients> coeffs;
    SpecularMagnetic::Execute(slices, kvec, coeffs);
    return coeffs;
}

const std::vector<MatrixRTCoefficients>&
getCoefficientsFromCache(kvector_t kvec, const std::vector<Slice>& slices,
                         MatrixFresnelMap::CoefficientHash& hash_table)
{
    auto it = hash_table.find(kvec);
    if (it == hash_table.end())
        it = hash_table.insert({kvec, calculateCoefficients(slices, kvec)}).first;
    return it->second;
}
}

