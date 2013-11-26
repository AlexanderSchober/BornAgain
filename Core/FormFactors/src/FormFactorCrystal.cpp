// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCrystal.cpp
//! @brief     Implements class FormFactorCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCrystal.h"

FormFactorCrystal::FormFactorCrystal(
        const Crystal& p_crystal,
        const IFormFactor& meso_crystal_form_factor,
        const IMaterial *p_material, complex_t wavevector_scattering_factor)
: m_lattice(p_crystal.getLattice())
, m_wavevector_scattering_factor(wavevector_scattering_factor)
, mp_ambient_material(p_material)
, m_max_rec_length(0.0)
{
    setName("FormFactorCrystal");
    mp_lattice_basis = p_crystal.createBasis();
    mp_basis_form_factor = mp_lattice_basis->createFormFactor(
            m_wavevector_scattering_factor);
    mp_meso_form_factor = meso_crystal_form_factor.clone();
    setAmbientMaterial(mp_ambient_material);
    calculateLargestReciprocalDistance();
}

FormFactorCrystal::~FormFactorCrystal()
{
    delete mp_lattice_basis;
    delete mp_basis_form_factor;
    delete mp_meso_form_factor;
}

FormFactorCrystal* FormFactorCrystal::clone() const
{
    Crystal np_crystal(*mp_lattice_basis, m_lattice);
    FormFactorCrystal *result = new FormFactorCrystal(np_crystal,
            *mp_meso_form_factor, mp_ambient_material,
            m_wavevector_scattering_factor);
    result->setName(getName());
    if (mP_transform.get()) {
        result->setTransformation(*mP_transform.get());
    }
    return result;
}

void FormFactorCrystal::setAmbientMaterial(const IMaterial *p_material)
{
    mp_lattice_basis->setAmbientMaterial(p_material);
    mp_basis_form_factor->setAmbientMaterial(p_material);
}

complex_t FormFactorCrystal::evaluate_for_q(const cvector_t& q) const
{
    (void)q;
    throw LogicErrorException("evaluate_for_q() should never be called"
            " explicitly for FormFactorCrystal");
}

complex_t FormFactorCrystal::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    // construct a real reciprocal vector
    cvector_t q_bin_lower = k_i - k_f_bin.m_q_lower;
    cvector_t q_bin_upper = k_i - k_f_bin.m_q_upper;
    Bin1DCVector q_bin;
    if (mP_inverse_transform.get()) {
        q_bin = Bin1DCVector(mP_inverse_transform->transformed(q_bin_lower),
                mP_inverse_transform->transformed(q_bin_upper));
    } else {
        q_bin = Bin1DCVector(q_bin_lower, q_bin_upper);
    }

    cvector_t q = q_bin.getMidPoint();
    kvector_t q_real(q.x().real(), q.y().real(), q.z().real());
    cvector_t k_zero;
    // calculate the used radius in function of the reciprocal lattice scale
    double radius = 2.1*m_max_rec_length;

    // retrieve nearest reciprocal lattice vectors
    m_lattice.computeReciprocalLatticeVectorsWithinRadius(q_real, radius);
    const KVectorContainer& rec_vectors = m_lattice.getKVectorContainer();

    // perform convolution on these lattice vectors
    complex_t result(0.0, 0.0);
    for (KVectorContainer::const_iterator it = rec_vectors.begin();
            it != rec_vectors.end(); ++it) {
        cvector_t q_i((*it).x(), (*it).y(), (*it).z());
        Bin1DCVector min_q_i_zero_bin(-q_i, -q_i);
        Bin1DCVector q_i_min_q(q_i - q_bin.m_q_lower, q_i - q_bin.m_q_upper);
        complex_t basis_factor = mp_basis_form_factor->evaluate(
                k_zero, min_q_i_zero_bin, alpha_f_bin);
        complex_t meso_factor = mp_meso_form_factor->evaluate(
                k_zero, q_i_min_q, alpha_f_bin);
        result += basis_factor*meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    double volume = m_lattice.getVolume();
    return result/volume;
}

Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    // construct a real reciprocal vector
    cvector_t q_bin_lower = k_i - k_f_bin.m_q_lower;
    cvector_t q_bin_upper = k_i - k_f_bin.m_q_upper;
    Bin1DCVector q_bin;
    if (mP_inverse_transform.get()) {
        q_bin = Bin1DCVector(mP_inverse_transform->transformed(q_bin_lower),
                mP_inverse_transform->transformed(q_bin_upper));
    } else {
        q_bin = Bin1DCVector(q_bin_lower, q_bin_upper);
    }

    cvector_t q = q_bin.getMidPoint();
    kvector_t q_real(q.x().real(), q.y().real(), q.z().real());
    cvector_t k_zero;
    // calculate the used radius in function of the reciprocal lattice scale
    double radius = 2.1*m_max_rec_length;

    // retrieve nearest reciprocal lattice vectors
    m_lattice.computeReciprocalLatticeVectorsWithinRadius(q_real, radius);
    const KVectorContainer& rec_vectors = m_lattice.getKVectorContainer();

    // perform convolution on these lattice vectors
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (KVectorContainer::const_iterator it = rec_vectors.begin();
            it != rec_vectors.end(); ++it) {
        cvector_t q_i((*it).x(), (*it).y(), (*it).z());
        Bin1DCVector min_q_i_zero_bin(-q_i, -q_i);
        Bin1DCVector q_i_min_q(q_i - q_bin.m_q_lower, q_i - q_bin.m_q_upper);

        //transform the matrix amplitude back!
        Eigen::Matrix2cd basis_factor;
        Eigen::Matrix2cd basis_factor_rotated = mp_basis_form_factor->
                evaluatePol(k_zero, min_q_i_zero_bin, alpha_f_bin, phi_f_bin);
        if (mP_transform.get()) {
            basis_factor = mP_transform->transformed(basis_factor_rotated);
        } else {
            basis_factor = basis_factor_rotated;
        }
        complex_t meso_factor = mp_meso_form_factor->evaluate(
                k_zero, q_i_min_q, alpha_f_bin);
        result += basis_factor*meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    double volume = m_lattice.getVolume();
    return result/volume;
}

double FormFactorCrystal::getVolume() const
{
    return mp_meso_form_factor->getVolume();
}

void FormFactorCrystal::setTransformation(
        const Geometry::ITransform3D& P_transform)
{
    mP_transform.reset(P_transform.clone());
    mP_inverse_transform.reset(mP_transform->inverse());
}

void FormFactorCrystal::calculateLargestReciprocalDistance()
{
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_max_rec_length = std::max(M_PI/a1.mag(), M_PI/a2.mag());
    m_max_rec_length = std::max(m_max_rec_length, M_PI/a3.mag());
}


