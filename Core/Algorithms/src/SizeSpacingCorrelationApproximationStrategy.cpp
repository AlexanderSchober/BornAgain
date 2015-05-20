// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SizeSpacingCorrelationApproximationStrategy.cpp
//! @brief     Implements class SizeSpacingCorrelationApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SizeSpacingCorrelationApproximationStrategy.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "MathFunctions.h"

SizeSpacingCorrelationApproximationStrategy::SizeSpacingCorrelationApproximationStrategy(
    SimulationParameters sim_params, double kappa)
    : IInterferenceFunctionStrategy(sim_params), m_mean_radius(0.0), m_kappa(kappa)
{
}

void SizeSpacingCorrelationApproximationStrategy::init(
    const SafePointerVector<FormFactorInfo> &form_factor_infos,
    const SafePointerVector<IInterferenceFunction> &ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException(
            "Wrong number of formfactors"
            " or interference functions for Size-Spacing Correlation Approximation.");
    }
    initMeanRadius();
}

double SizeSpacingCorrelationApproximationStrategy::evaluateForList(
    const cvector_t &k_i, const Bin1DCVector &k_f_bin, const std::vector<complex_t> &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    double diffuse_intensity = 0.0;
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        complex_t ff = ff_list[i];
        double fraction = m_ff_infos[i]->m_abundance / total_abundance;
        diffuse_intensity += fraction * (std::norm(ff));
    }
    complex_t mcff = getMeanCharacteristicFF(k_i, k_f_bin, ff_list);
    complex_t mcffc = getMeanConjCharacteristicFF(k_i, k_f_bin, ff_list);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0 * m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    double interference_intensity = 2.0 * (mcff * mcffc * omega / (1.0 - p2kappa * omega)).real();
    return total_abundance * (diffuse_intensity + interference_intensity);
}

double SizeSpacingCorrelationApproximationStrategy::evaluateForMatrixList(
    const SimulationElement& sim_element, const MatrixFFVector &ff_list) const
{
    double wavelength = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(wavelength, alpha_i, phi_i);
    Bin1D alpha_f_bin(sim_element.getAlphaMin(), sim_element.getAlphaMax());
    Bin1D phi_f_bin(sim_element.getPhiMin(), sim_element.getPhiMax());
    Bin1DCVector k_f_bin(wavelength, alpha_f_bin, phi_f_bin);

    double qp = getqp(k_i, k_f_bin);
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        Eigen::Matrix2cd ff = ff_list[i];
        double fraction = m_ff_infos[i]->m_abundance / total_abundance;
        diffuse_matrix += fraction * (ff * sim_element.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd mcff = getMeanCharacteristicMatrixFF(k_i, k_f_bin, ff_list);
    Eigen::Matrix2cd mcffc = getMeanConjCharacteristicMatrixFF(k_i, k_f_bin, ff_list);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0 * m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    Eigen::Matrix2cd interference_matrix
        = (2.0 * omega / (1.0 - p2kappa * omega))
          * (sim_element.getAnalyzerOperator() * mcff * sim_element.getPolarization() * mcffc);
    Eigen::Matrix2cd diffuse_matrix2 = sim_element.getAnalyzerOperator() * diffuse_matrix;
    double interference_trace = std::abs(interference_matrix.trace());
    double diffuse_trace = std::abs(diffuse_matrix2.trace());
    return total_abundance * (diffuse_trace + interference_trace);
}

bool SizeSpacingCorrelationApproximationStrategy::checkVectorSizes() const
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs > 0 && n_ifs == 1);
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanCharacteristicFF(
    const cvector_t &k_i, const Bin1DCVector &k_f_bin, const std::vector<complex_t> &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    complex_t result(0.0, 0.0);
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        result += m_ff_infos[i]->m_abundance * ff_list[i]
                  * calculatePositionOffsetPhase(qp, m_kappa, i);
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return result;
    return result / total_abundance;
}

Eigen::Matrix2cd SizeSpacingCorrelationApproximationStrategy::getMeanCharacteristicMatrixFF(
    const cvector_t &k_i, const Bin1DCVector &k_f_bin,
    const MatrixFFVector &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        result += m_ff_infos[i]->m_abundance * calculatePositionOffsetPhase(qp, m_kappa, i)
                  * ff_list[i];
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return result;
    return result / total_abundance;
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanConjCharacteristicFF(
    const cvector_t &k_i, const Bin1DCVector &k_f_bin, const std::vector<complex_t> &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    complex_t result(0.0, 0.0);
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        result += m_ff_infos[i]->m_abundance * std::conj(ff_list[i])
                  * calculatePositionOffsetPhase(qp, m_kappa, i);
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return result;
    return result / total_abundance;
}

Eigen::Matrix2cd SizeSpacingCorrelationApproximationStrategy::getMeanConjCharacteristicMatrixFF(
    const cvector_t &k_i, const Bin1DCVector &k_f_bin,
    const MatrixFFVector &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        result += m_ff_infos[i]->m_abundance * calculatePositionOffsetPhase(qp, m_kappa, i)
                  * ff_list[i].adjoint();
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return result;
    return result / total_abundance;
}

complex_t
SizeSpacingCorrelationApproximationStrategy::getCharacteristicDistribution(double qp) const
{
    const InterferenceFunctionRadialParaCrystal *p_iff
        = dynamic_cast<const InterferenceFunctionRadialParaCrystal *>(m_ifs[0]);
    if (p_iff == 0) {
        throw ClassInitializationException("Wrong interference function for SSCA");
    }
    return p_iff->FTPDF(qp);
}

complex_t
SizeSpacingCorrelationApproximationStrategy::getCharacteristicSizeCoupling(double qp,
                                                                           double kappa) const
{
    size_t n_frs = m_ff_infos.size();
    complex_t result = complex_t(0.0, 0.0);
    double total_abundance = 0.0;
    for (size_t i = 0; i < n_frs; ++i) {
        result += m_ff_infos[i]->m_abundance * calculatePositionOffsetPhase(qp, kappa, i);
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance <= 0.0)
        return result;
    return result / total_abundance;
}

complex_t
SizeSpacingCorrelationApproximationStrategy::calculatePositionOffsetPhase(double qp, double kappa,
                                                                          size_t index) const
{
    return std::exp(complex_t(0.0, 1.0) * kappa * qp
                    * (m_ff_infos[index]->mp_ff->getRadius() - m_mean_radius));
}

double SizeSpacingCorrelationApproximationStrategy::getqp(const cvector_t &k_i,
                                                          const Bin1DCVector &k_f_bin) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    double qxr = q.x().real();
    double qyr = q.y().real();
    return std::sqrt(qxr * qxr + qyr * qyr);
}

void SizeSpacingCorrelationApproximationStrategy::initMeanRadius()
{
    m_mean_radius = 0.0;
    double total_abundance = 0.0;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        m_mean_radius += m_ff_infos[i]->m_abundance * m_ff_infos[i]->mp_ff->getRadius();
        total_abundance += m_ff_infos[i]->m_abundance;
    }
    if (total_abundance > 0.0)
        m_mean_radius /= total_abundance;
}
