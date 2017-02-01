// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationTerm.h
//! @brief     Defines interface IComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPUTATIONTERM_H
#define ICOMPUTATIONTERM_H

#include "SafePointerVector.h"
#include <vector>


class ILayerSpecularInfo;
class MultiLayer;
//class ProgressHandler;
//class SimulationElement;
//class SimulationOptions;

//! Computes an independent term of the scattering intensity.
//! Controlled by MainComputation, which adds up all contributions from subclasses
//! of IComputationTerm
//! @ingroup algorithms_internal

class IComputationTerm
{
public:
    IComputationTerm(const MultiLayer* p_multilayer);
    virtual ~IComputationTerm();

    //! Sets magnetic reflection/transmission info for all layers
    void setSpecularInfo(const SafePointerVector<ILayerSpecularInfo>* p_specular_info);

//    void eval(const SimulationOptions& options,
//              ProgressHandler* progress,
//              bool polarized,
//              const std::vector<SimulationElement>::iterator& begin_it,
//              const std::vector<SimulationElement>::iterator& end_it) const;

protected:
    const MultiLayer* mp_multilayer;
    const SafePointerVector<ILayerSpecularInfo>* mp_specular_info_map;
};

#endif // ICOMPUTATIONTERM_H
