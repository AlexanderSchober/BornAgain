// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DSuperLattice.cpp
//! @brief     Implements class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunction2DSuperLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "IntegratorReal.h"
#include "InterferenceFunctionNone.h"
#include "Macros.h"
#include "MathConstants.h"
#include "RealParameter.h"

#include <limits>

namespace {
double SinNx_Div_Sinx(double x, unsigned N);
double DebyeWallerFactor(double variance, double q2);
}


InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
        const Lattice2D& lattice, unsigned size_1, unsigned size_2)
    : m_sigma2(0.0)
    , m_integrate_xi(false)
    , mP_substructure(nullptr)
    , m_size_1(size_1)
    , m_size_2(size_2)
{
    setName(BornAgain::InterferenceFunction2DSuperLattice);
    setLattice(lattice);
    setSubstructureIFF(InterferenceFunctionNone());
    init_parameters();
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector  in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
        double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)
    : m_sigma2(0.0)
    , m_integrate_xi(false)
    , mP_substructure(nullptr)
    , m_size_1(size_1)
    , m_size_2(size_2)
{
    setName(BornAgain::InterferenceFunction2DSuperLattice);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
    setSubstructureIFF(InterferenceFunctionNone());
    init_parameters();
}

InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice() =default;

InterferenceFunction2DSuperLattice* InterferenceFunction2DSuperLattice::clone() const
{
    return new InterferenceFunction2DSuperLattice(*this);
}

void InterferenceFunction2DSuperLattice::setSubstructureIFF(const IInterferenceFunction& sub_iff)
{
    mP_substructure.reset(sub_iff.clone());
    registerChild(mP_substructure.get());
}

const IInterferenceFunction& InterferenceFunction2DSuperLattice::substructureIFF() const
{
    return *mP_substructure;
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DSuperLattice* InterferenceFunction2DSuperLattice::createSquare(
    double lattice_length, double xi, unsigned size_1, unsigned size_2)
{
    return new InterferenceFunction2DSuperLattice(SquareLattice(lattice_length, xi),
                                                   size_1, size_2);
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DSuperLattice* InterferenceFunction2DSuperLattice::createHexagonal(
    double lattice_length, double xi, unsigned size_1, unsigned size_2)
{
    return new InterferenceFunction2DSuperLattice(HexagonalLattice(lattice_length, xi),
                                                   size_1, size_2);
}

double InterferenceFunction2DSuperLattice::evaluate(const kvector_t q) const
{
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(mP_lattice->rotationAngle());
    return mP_integrator->integrate(0.0, M_TWOPI) / M_TWOPI;
}

void InterferenceFunction2DSuperLattice::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
    mP_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunction2DSuperLattice::lattice() const
{
    if(!mP_lattice)
        throw std::runtime_error("InterferenceFunctionFinite2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *mP_lattice;
}

std::vector<const INode*> InterferenceFunction2DSuperLattice::getChildren() const
{
    return std::vector<const INode*>() << mP_lattice << mP_substructure;
}

InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
        const InterferenceFunction2DSuperLattice& other)
    : m_sigma2(other.m_sigma2)
    , m_size_1(other.m_size_1)
    , m_size_2(other.m_size_2)
{
    setName(other.getName());
    if(other.mP_lattice)
        setLattice(*other.mP_lattice);
    setSubstructureIFF(*other.mP_substructure);
    setIntegrationOverXi(other.integrationOverXi());
    init_parameters();
}

void InterferenceFunction2DSuperLattice::setLattice(const Lattice2D& lattice)
{
    mP_lattice.reset(lattice.clone());
    registerChild(mP_lattice.get());
}

void InterferenceFunction2DSuperLattice::init_parameters()
{
    registerParameter(BornAgain::PositionVariance, &m_sigma2).setNonnegative();
    mP_integrator
        = make_integrator_real(this, &InterferenceFunction2DSuperLattice::interferenceForXi);
}

double InterferenceFunction2DSuperLattice::interferenceForXi(double xi) const
{
    double a = mP_lattice->length1();
    double b = mP_lattice->length2();
    double xialpha = xi + mP_lattice->latticeAngle();

    double qadiv2 = (m_qx*a*std::cos(xi) + m_qy*a*std::sin(xi)) / 2.0;
    double qbdiv2 = (m_qx*b*std::cos(xialpha) + m_qy*b*std::sin(xialpha)) / 2.0;
    double ampl = SinNx_Div_Sinx(qadiv2, m_size_1)*SinNx_Div_Sinx(qbdiv2, m_size_2);
    double lattice_factor = ampl*ampl / (m_size_1*m_size_2);
    double DW_factor = DebyeWallerFactor(m_sigma2, m_qx*m_qx + m_qy*m_qy);

    double delta_xi = xi - mP_lattice->rotationAngle();
    kvector_t q = kvector_t(m_qx, m_qy, 0.0).rotatedZ(-delta_xi);
    double substructure_result = mP_substructure->evaluate(q);

    return (1.0 + DW_factor*(lattice_factor - 1.0))*substructure_result;
}

namespace {
double SinNx_Div_Sinx(double x, unsigned N) {
    static const double SQRT6DOUBLE_EPS = std::sqrt(6.0*std::numeric_limits<double>::epsilon());
    auto nd = static_cast<double>(N);
    if(std::abs(nd*x) < SQRT6DOUBLE_EPS)
        return nd;
    double num = std::sin(nd*x);
    double den = std::sin(x);
    return num/den;
}
double DebyeWallerFactor(double variance, double q2) {
    return std::exp(-q2*variance/2.0);
}
}

