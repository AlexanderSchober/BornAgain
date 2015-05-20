// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DecouplingApproximationStrategy.cpp
//! @brief     Implements class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"
#include "MathFunctions.h"

#include <cassert>
#include <iostream>

void
DecouplingApproximationStrategy::init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
                                      const SafePointerVector<IInterferenceFunction> &ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions "
                                           "for Decoupling Approximation.");
    }
}

double DecouplingApproximationStrategy::evaluateForList(const cvector_t &k_i,
                                                        const Bin1DCVector &k_f_bin,
                                                        const std::vector<complex_t> &ff_list) const
{
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        complex_t ff = ff_list[i];

        if (MathFunctions::isnan(ff.real())) {
            throw RuntimeErrorException("DecouplingApproximationStrategy::evaluateForList() -> "
                                        "Error! Amplitude is NaN");
        }
        double fraction = m_ff_infos[i]->m_abundance / total_abundance;
        amplitude += fraction * ff;
        intensity += fraction * (std::norm(ff));
    }
    double amplitude_norm = std::norm(amplitude);
    double itf_function = m_ifs[0]->evaluate(k_i - k_f_bin.getMidPoint());
    return total_abundance * (intensity + amplitude_norm * (itf_function - 1.0));
}

double DecouplingApproximationStrategy::evaluateForMatrixList(const SimulationElement& sim_element,
                                                              const MatrixFFVector &ff_list) const
{
    double wavelength = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i, k_f;
    k_i.setLambdaAlphaPhi(wavelength, alpha_i, phi_i);
    k_f.setLambdaAlphaPhi(wavelength, sim_element.getAlphaMean(), sim_element.getPhiMean());

    Eigen::Matrix2cd mean_intensity = Eigen::Matrix2cd::Zero();
    Eigen::Matrix2cd mean_amplitude = Eigen::Matrix2cd::Zero();

    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        Eigen::Matrix2cd ff = ff_list[i];

        if (!ff.allFinite()) {
            throw RuntimeErrorException("DecouplingApproximationStrategy::evaluateForList() -> "
                                        "Error! Form factor contains NaN or infinite");
        }
        double fraction = m_ff_infos[i]->m_abundance / total_abundance;
        mean_amplitude += fraction * ff;
        mean_intensity += fraction * (ff * sim_element.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd amplitude_matrix = sim_element.getAnalyzerOperator() * mean_amplitude
            * sim_element.getPolarization() * mean_amplitude.adjoint();
    Eigen::Matrix2cd intensity_matrix = sim_element.getAnalyzerOperator() * mean_intensity;
    double amplitude_trace = std::abs(amplitude_matrix.trace());
    double intensity_trace = std::abs(intensity_matrix.trace());
//    double itf_function = m_ifs[0]->evaluate(k_i - k_f_bin.getMidPoint());
    double itf_function = m_ifs[0]->evaluate(k_i - k_f);
    return total_abundance * (intensity_trace + amplitude_trace * (itf_function - 1.0));
}

bool DecouplingApproximationStrategy::checkVectorSizes() const
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs > 0 && n_ifs == 1);
}
