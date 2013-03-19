// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/StrategyBuilder.h 
//! @brief     Defines classes LayerDecoratorStrategyBuilder, FormFactorInfo. 
//
// ************************************************************************** //

#ifndef STRATEGYBUILDER_H_
#define STRATEGYBUILDER_H_

#include "SimulationParameters.h"
#include "SafePointerVector.h"
#include "ICloneable.h"
#include "Types.h"

class FormFactorInfo;
class IInterferenceFunction;
class IInterferenceFunctionStrategy;
class LayerDecorator;
class Simulation;
class IDoubleToPairOfComplexMap;
class ParticleInfo;
class IFormFactor;

//- -------------------------------------------------------------------
//! @class LayerDecoratorStrategyBuilder
//! @brief Definition of methods to generate a simulation strategy from
//! a LayerDecorator and SimulationParameters
//- -------------------------------------------------------------------
class LayerDecoratorStrategyBuilder
{
public:
    LayerDecoratorStrategyBuilder(const LayerDecorator &decorated_layer,
            const Simulation &simulation, const SimulationParameters &sim_params);
    virtual ~LayerDecoratorStrategyBuilder();

    //! set R and T coefficient map for DWBA simulation
    void setReflectionTransmissionFunction(const IDoubleToPairOfComplexMap &rt_map);

    //! create a strategy object which is able to calculate the scattering for fixed k_f
    virtual IInterferenceFunctionStrategy *createStrategy();
protected:
    LayerDecorator *mp_layer_decorator;         //!< decorated layer
    Simulation *mp_simulation;                  //!< simulation
    SimulationParameters m_sim_params;          //!< simulation parameters
    IDoubleToPairOfComplexMap *mp_RT_function;  //!< R and T coefficients for DWBA
private:
    //! collect the formfactor info of all particles in the decoration and decorate
    //! these for DWBA when needed
    void collectFormFactorInfos();
    //! collect the interference functions
    void collectInterferenceFunctions();
    //! retrieve wavelength from simulation
    double getWavelength();
    //! create formfactor info for single particle
    FormFactorInfo *createFormFactorInfo(const ParticleInfo *p_particle_info,
            complex_t n_ambient_refractive_index, complex_t factor) const;

    SafePointerVector<FormFactorInfo> m_ff_infos;
    SafePointerVector<IInterferenceFunction> m_ifs;
};

class FormFactorInfo : public ICloneable
{
public:
    FormFactorInfo();
    ~FormFactorInfo();
    virtual FormFactorInfo *clone() const;
    IFormFactor *mp_ff;
    double m_pos_x, m_pos_y;
    double m_abundance;
};

#endif /* STRATEGYBUILDER_H_ */
