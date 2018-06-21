// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IInterferenceFunctionStrategy.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorCoherentSum.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "IntegratorMCMiser.h"
#include "IFresnelMap.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "WavevectorInfo.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(const SimulationOptions& sim_params,
                                                             bool polarized)
    : mP_iff(nullptr)
    , m_options(sim_params)
    , m_polarized(polarized)
    , mP_integrator(make_integrator_miser(
        this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles, 2) )
{}

IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy() =default;

void IInterferenceFunctionStrategy::init(
    const SafePointerVector<FormFactorCoherentSum>& weighted_formfactors,
    const IInterferenceFunction* p_iff)
{
    if (weighted_formfactors.size()==0)
        throw Exceptions::ClassInitializationException(
                "IInterferenceFunctionStrategy::init: strategy gets no formfactors.");
    m_formfactor_wrappers = weighted_formfactors;
    if (p_iff)
        mP_iff.reset(p_iff->clone());
    else
        mP_iff.reset(new InterferenceFunctionNone());

    strategy_specific_post_init();
}

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate() && (sim_element.getSolidAngle() > 0.0))
        return MCIntegratedEvaluate(sim_element);
    return evaluateSinglePoint(sim_element);
}

std::vector<complex_t> IInterferenceFunctionStrategy::precomputeScalar(
        const SimulationElement& sim_element,
        const SafePointerVector<FormFactorCoherentSum>& ff_wrappers)
{
    std::vector<complex_t> result;
    for (auto ffw: ff_wrappers) {
        result.push_back(ffw->evaluate(sim_element));
    }
    return result;
}

IInterferenceFunctionStrategy::matrixFFVector_t
IInterferenceFunctionStrategy::precomputePolarized(
        const SimulationElement& sim_element,
        const SafePointerVector<FormFactorCoherentSum>& ff_wrappers)
{
    matrixFFVector_t result;
    for (auto ffw: ff_wrappers) {
        result.push_back(ffw->evaluatePol(sim_element));
    }
    return result;
}

double IInterferenceFunctionStrategy::evaluateSinglePoint(
        const SimulationElement& sim_element) const
{
    if (!m_polarized)
        return scalarCalculation(sim_element);
    else
        return polarizedCalculation(sim_element);
}

//! Performs a Monte Carlo integration over the bin for the evaluation of the intensity.
double IInterferenceFunctionStrategy::MCIntegratedEvaluate(
    const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator->integrate(
        min_array, max_array, (void*)&sim_element, m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(
    double* fractions, size_t, void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    return pars->getIntegrationFactor(par0, par1) * evaluateSinglePoint(sim_element);
}

void IInterferenceFunctionStrategy::strategy_specific_post_init()
{}
