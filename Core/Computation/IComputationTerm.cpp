// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationTerm.cpp
//! @brief     Implements part of interface IComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IComputationTerm.h"


IComputationTerm::IComputationTerm(const MultiLayer* p_multilayer)
    : mp_multilayer(p_multilayer)
    , mp_specular_info_map(nullptr)
{}

IComputationTerm::~IComputationTerm()
{}

void IComputationTerm::setSpecularInfo(
        const SafePointerVector<ILayerSpecularInfo>* p_specular_info)
{
    mp_specular_info_map = p_specular_info;
}
