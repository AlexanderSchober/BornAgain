// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/MultiLayerDWBASimulation.h
//! @brief     Defines class MultiLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERDWBASIMULATION_H_
#define MULTILAYERDWBASIMULATION_H_

#include "LayerDWBASimulation.h"
#include "SafePointerVector.h"

#include <set>
#include <map>

class MultiLayer;
class MultiLayerRoughnessDWBASimulation;


//! @class MultiLayerDWBASimulation
//! @ingroup algorithms_internal
//! @brief This is the class that will perform a DWBA calculation with the given
//! sample and simulation parameters

class BA_CORE_API_ MultiLayerDWBASimulation : public DWBASimulation
{
public:
    MultiLayerDWBASimulation(const MultiLayer *p_multi_layer);
    virtual ~MultiLayerDWBASimulation();

    MultiLayerDWBASimulation *clone() const
    {
        throw NotImplementedException(
            "MultiLayerDWBASimulation::clone() -> Error: not implemented");
    }

    virtual void init(const GISASSimulation& simulation,
                      std::vector<SimulationElement>::iterator begin_it,
                      std::vector<SimulationElement>::iterator end_it);

    //! Sets thread information for masking
    virtual void setThreadInfo(const ThreadInfo& thread_info);

    virtual void run();

protected:
    virtual void runProtected();

    //! calculates intensity map for samples with magnetization
    void collectRTCoefficientsScalar();
    void collectRTCoefficientsMatrix();
    bool requiresMatrixRTCoefficients() const;

    std::map<size_t, SafePointerVector<LayerDWBASimulation> > m_layer_dwba_simulations_map;
    MultiLayer *mp_multi_layer;
    MultiLayerRoughnessDWBASimulation *mp_roughness_dwba_simulation;
};

#endif /* MULTILAYERDWBASIMULATION_H_ */
