// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/MultiLayerDWBASimulation.cpp
//! @brief     Implements class MultiLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerDWBASimulation.h"

#include "SpecularMatrix.h"
#include "SpecularMagnetic.h"
#include "MultiLayer.h"
#include "MultiLayerRoughnessDWBASimulation.h"
#include "MessageService.h"
#include "ScalarSpecularInfoMap.h"
#include "MatrixSpecularInfoMap.h"
#include "SamplePreprocessor.h"
#include "BornAgainNamespace.h"

#include <boost/scoped_ptr.hpp>


MultiLayerDWBASimulation::MultiLayerDWBASimulation(
        const MultiLayer* p_multi_layer)
  : mp_roughness_dwba_simulation(0)
{
    mp_multi_layer = p_multi_layer->clone();
    SamplePreprocessor preprocessor;
    preprocessor.process(mp_multi_layer);
}

MultiLayerDWBASimulation::~MultiLayerDWBASimulation()
{
    delete mp_multi_layer;
    delete mp_roughness_dwba_simulation;
}

void MultiLayerDWBASimulation::init(const Simulation& simulation,
                                    std::vector<SimulationElement>::iterator begin_it,
                                    std::vector<SimulationElement>::iterator end_it)
{
    msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::init()";
    DWBASimulation::init(simulation, begin_it, end_it);
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        for (size_t j=0; j<mp_multi_layer->getLayer(i)->getNumberOfLayouts(); ++j) {
            LayerDWBASimulation *p_layer_dwba_sim =
                mp_multi_layer->getLayer(i)->createLayoutSimulation(j);
            if (p_layer_dwba_sim) {
                if (m_layer_dwba_simulations_map.find(i)
                    == m_layer_dwba_simulations_map.end()) {
                    m_layer_dwba_simulations_map[i] =
                            SafePointerVector<LayerDWBASimulation>();
                }
                m_layer_dwba_simulations_map[i].push_back(p_layer_dwba_sim);
            }
        }

    }
    // scattering from rough surfaces in DWBA
    for (size_t i=0; i<mp_multi_layer->getNumberOfInterfaces(); ++i) {
        if(mp_multi_layer->getLayerInterface(i)->getRoughness() ) {
            mp_roughness_dwba_simulation =
                new MultiLayerRoughnessDWBASimulation(mp_multi_layer);
            break;
        }
    }
}

void MultiLayerDWBASimulation::run()
{
    setStatus(RUNNING);
    try {
        runProtected();
        setStatus(COMPLETED);
    }
    catch(const std::exception &ex) {
        setRunMessage(std::string(ex.what()));
        setStatus(FAILED);
    }
}

void MultiLayerDWBASimulation::runProtected()
{
    msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::runProtected()";
    m_dwba_intensity.setAllTo(0.0);

    if (requiresMatrixRTCoefficients()) {
        collectRTCoefficientsMatrix();
    }
    else {
        collectRTCoefficientsScalar();
    }

    // run through layers and run layer simulations
    std::vector<SimulationElement> layer_elements;
    std::copy(m_begin_it, m_end_it, std::back_inserter(layer_elements));
    for (std::map<size_t, SafePointerVector<LayerDWBASimulation> >::
         iterator it = m_layer_dwba_simulations_map.begin();
            it != m_layer_dwba_simulations_map.end(); ++it)
    {
        for (size_t i=0; i<it->second.size(); ++i) {
            LayerDWBASimulation *p_layer_dwba_sim = it->second[i];
            p_layer_dwba_sim->init(*mp_simulation, layer_elements.begin(), layer_elements.end());
            p_layer_dwba_sim->run();
            AddElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
        }
    }

    if (!requiresMatrixRTCoefficients() && mp_roughness_dwba_simulation) {
        msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::run() -> roughness";
        mp_roughness_dwba_simulation->init(*mp_simulation, layer_elements.begin(),
                                           layer_elements.end());
        mp_roughness_dwba_simulation->run();
        AddElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }
}

void MultiLayerDWBASimulation::collectRTCoefficientsScalar()
{
    double lambda = m_begin_it->getWavelength();
    double alpha_i = m_begin_it->getAlphaI();
    double phi_i = m_begin_it->getPhiI();
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, phi_i);

    // the coefficients for the incoming wavevector are calculated on the
    // original sample
    SpecularMatrix specularCalculator;
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    specularCalculator.execute(*mp_multi_layer, k_i, coeffs);

    // run through layers and construct T,R functions
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::run()"
                "-> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        ScalarSpecularInfoMap *p_coeff_map = new ScalarSpecularInfoMap(
                    mp_multi_layer, i_layer, lambda);
        layer_coeff_map.addOutCoefficients(p_coeff_map);

        // add reflection/transmission coeffs from incoming beam
        layer_coeff_map.addInCoefficients(new ScalarRTCoefficients(
                coeffs[i_layer]));

        // layer DWBA simulation
        std::map<size_t, SafePointerVector<LayerDWBASimulation> >
                ::iterator pos = m_layer_dwba_simulations_map.find(i_layer);
        if(pos != m_layer_dwba_simulations_map.end() ) {
            for (size_t i=0; i<pos->second.size();++i) {
                LayerDWBASimulation *p_layer_dwba_sim = pos->second[i];
                p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
            }
        }

        // layer roughness DWBA
        if(mp_roughness_dwba_simulation) {
            mp_roughness_dwba_simulation->setSpecularInfo(i_layer,
                    layer_coeff_map);
        }

    } // i_layer
}

void MultiLayerDWBASimulation::collectRTCoefficientsMatrix()
{
    double lambda = m_begin_it->getWavelength();
    double alpha_i = m_begin_it->getAlphaI();
    double phi_i = m_begin_it->getPhiI();
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, phi_i);

    // the coefficients for the incoming wavevector are calculated on the
    // original sample
    SpecularMagnetic specularCalculator;
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    specularCalculator.execute(*mp_multi_layer, k_i, coeffs);

    // run through layers and add DWBA from each layer
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::runMagnetic()"
                "-> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        MatrixSpecularInfoMap *p_coeff_map = new MatrixSpecularInfoMap(
                    mp_multi_layer, i_layer, lambda);
        layer_coeff_map.addOutCoefficients(p_coeff_map);

        // add reflection/transmission coeffs from incoming beam
        layer_coeff_map.addInCoefficients(new MatrixRTCoefficients(
                coeffs[i_layer]));

        // layer DWBA simulation
        std::map<size_t, SafePointerVector<LayerDWBASimulation> >
             ::iterator pos = m_layer_dwba_simulations_map.find(i_layer);
        if(pos != m_layer_dwba_simulations_map.end() ) {
            for (size_t i=0; i<pos->second.size();++i) {
                LayerDWBASimulation *p_layer_dwba_sim = pos->second[i];
                p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
            }
        }
    } // i_layer
}

bool MultiLayerDWBASimulation::requiresMatrixRTCoefficients() const
{
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        const Layer *p_layer = mp_multi_layer->getLayer(i);
        const IMaterial *p_material = p_layer->getMaterial();
        if (!p_material->isScalarMaterial()) return true;
    }
    return false;
}
