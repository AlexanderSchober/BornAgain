// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationTerm.cpp
//! @brief     Implements part of interface IComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IComputationTerm.h"


IComputationTerm::IComputationTerm(const MultiLayer* p_multilayer,
                                   const IFresnelMap* p_fresnel_map)
    : mp_multilayer(p_multilayer)
    , mp_fresnel_map(p_fresnel_map)
{}

IComputationTerm::~IComputationTerm()
{}

void IComputationTerm::mergeRegionMap(
        std::map<size_t, std::vector<HomogeneousRegion> >& region_map) const
{
    for (auto& entry : m_region_map)
    {
        size_t i = entry.first;
        auto& regions = entry.second;
        region_map[i].insert(region_map[i].begin(), regions.begin(), regions.end());
    }
}
