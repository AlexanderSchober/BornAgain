// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Beam.cpp
//! @brief     Implements class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Beam.h"
#include "Exceptions.h"
#include "Numeric.h"
#include <Eigen/LU>

Beam::Beam() : m_wavelength(1.0), m_alpha(0.0), m_phi(0.0), m_intensity(0.0)
{
    setName("Beam");
    init_parameters();
    initPolarization();
}

Beam::Beam(const Beam &other)
    : IParameterized(), m_wavelength(other.m_wavelength), m_alpha(other.m_alpha),
      m_phi(other.m_phi), m_intensity(other.m_intensity), m_polarization(other.m_polarization)
{
    setName(other.getName());
    init_parameters();
}

Beam &Beam::operator=(const Beam &other)
{
    if (this != &other) {
        Beam tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

cvector_t Beam::getCentralK() const
{
    cvector_t k;
    k.setLambdaAlphaPhi(m_wavelength, -1.0 * m_alpha, m_phi);
    return k;
}

void Beam::setCentralK(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength <= 0.0) {
        throw Exceptions::ClassInitializationException(
            "Beam::setCentralK() -> Error. Wavelength can't be negative or zero.");
    }
    if (alpha_i < 0.0) {
        throw Exceptions::ClassInitializationException(
            "Beam::setCentralK() -> Error. Inclination angle alpha_i can't be negative.");
    }
    m_wavelength = wavelength;
    m_alpha = alpha_i;
    m_phi = phi_i;
}

void Beam::setPolarization(const kvector_t &bloch_vector)
{
    if (bloch_vector.mag() > 1.0) {
        throw Exceptions::ClassInitializationException("Beam::setPolarization: The given Bloch "
                                                       "vector cannot represent a real physical "
                                                       "ensemble");
    }
    m_polarization = calculatePolarization(bloch_vector);
}

Eigen::Matrix2cd Beam::calculatePolarization(const kvector_t &bloch_vector) const
{
    Eigen::Matrix2cd result;
    double x = bloch_vector.x();
    double y = bloch_vector.y();
    double z = bloch_vector.z();
    complex_t im(0.0, 1.0);
    result(0, 0) = (1.0 + z) / 2.0;
    result(0, 1) = (x - im * y) / 2.0;
    result(1, 0) = (x + im * y) / 2.0;
    result(1, 1) = (1.0 - z) / 2.0;
    return result;
}

void Beam::init_parameters()
{
    clearParameterPool();
    registerParameter("intensity", &m_intensity);
    registerParameter("wavelength", &m_wavelength, AttLimits::positive());
    registerParameter("alpha", &m_alpha, AttLimits::lowerLimited(0.0));
    registerParameter("phi", &m_phi);
}

void Beam::swapContent(Beam &other)
{
    std::swap(this->m_wavelength, other.m_wavelength);
    std::swap(this->m_alpha, other.m_alpha);
    std::swap(this->m_phi, other.m_phi);
    std::swap(this->m_intensity, other.m_intensity);
    std::swap(this->m_polarization, other.m_polarization);
}

void Beam::initPolarization()
{
    kvector_t zero;
    setPolarization(zero);
}

void Beam::print(std::ostream &ostr) const
{
    ostr << "Beam: '" << getName() << "' " << m_parameters;
}
