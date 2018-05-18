// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DLattice.cpp
//! @brief     Implements class InterferenceFunction2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunction2DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "IntegratorReal.h"
#include "Macros.h"
#include "MathConstants.h"
#include "RealParameter.h"


InterferenceFunction2DLattice::InterferenceFunction2DLattice(const Lattice2D& lattice)
    : m_integrate_xi(false)
{
    setName(BornAgain::InterferenceFunction2DLatticeType);
    setLattice(lattice);
    init_parameters();
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector  in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
InterferenceFunction2DLattice::InterferenceFunction2DLattice(double length_1, double length_2,
                                                             double alpha, double xi)
    : m_integrate_xi(false)
    , m_na(0), m_nb(0)
{
    setName(BornAgain::InterferenceFunction2DLatticeType);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
    init_parameters();
}

InterferenceFunction2DLattice::~InterferenceFunction2DLattice()
{
}

InterferenceFunction2DLattice* InterferenceFunction2DLattice::clone() const
{
    return new InterferenceFunction2DLattice(*this);
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DLattice* InterferenceFunction2DLattice::createSquare(
double lattice_length, double xi)
{
    return new InterferenceFunction2DLattice(SquareLattice(lattice_length, xi));
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DLattice* InterferenceFunction2DLattice::createHexagonal(
    double lattice_length, double xi)
{
    return new InterferenceFunction2DLattice(HexagonalLattice(lattice_length, xi));
}

//! Sets two-dimensional decay function.
//! @param decay: two-dimensional decay function in reciprocal space
void InterferenceFunction2DLattice::setDecayFunction(const IFTDecayFunction2D& decay)
{
    m_decay.reset(decay.clone());
    registerChild(m_decay.get());
    initialize_calc_factors();
}

double InterferenceFunction2DLattice::evaluate(const kvector_t q) const
{
    if (!m_decay)
        throw Exceptions::NullPointerException("InterferenceFunction2DLattice::evaluate"
                                               " -> Error! No decay function defined.");
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(m_lattice->rotationAngle());
    return mP_integrator->integrate(0.0, M_TWOPI) / M_TWOPI;
}

void InterferenceFunction2DLattice::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
    m_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunction2DLattice::lattice() const
{
    if(!m_lattice)
        throw std::runtime_error("InterferenceFunction2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}

double InterferenceFunction2DLattice::getParticleDensity() const
{
    double area = m_lattice->unitCellArea();
    return area == 0.0 ? 0.0 : 1.0/area;
}

std::vector<const INode*> InterferenceFunction2DLattice::getChildren() const
{
    return std::vector<const INode*>() << m_decay << m_lattice;
}

void InterferenceFunction2DLattice::onChange()
{
    initialize_rec_vectors();
    initialize_calc_factors();
}

InterferenceFunction2DLattice::InterferenceFunction2DLattice(
        const InterferenceFunction2DLattice& other)
{
    setName(other.getName());
    if(other.m_lattice)
        setLattice(*other.m_lattice);
    if(other.m_decay)
        setDecayFunction(*other.m_decay);
    setIntegrationOverXi(other.integrationOverXi());
    init_parameters();
}

void InterferenceFunction2DLattice::setLattice(const Lattice2D& lattice)
{
    m_lattice.reset(lattice.clone());
    registerChild(m_lattice.get());
    initialize_rec_vectors();
}

void InterferenceFunction2DLattice::init_parameters()
{
    mP_integrator
        = make_integrator_real(this, &InterferenceFunction2DLattice::interferenceForXi);
}

double InterferenceFunction2DLattice::interferenceForXi(double xi) const
{
    double result = 0.0;
    double qx_frac, qy_frac;
    calculateReciprocalVectorFraction(m_qx, m_qy, xi, qx_frac, qy_frac);

    for (int i = -m_na - 1; i < m_na + 2; ++i) {
        for (int j = -m_nb - 1; j < m_nb + 2; ++j) {
            double qx = qx_frac + i * m_sbase.m_asx + j * m_sbase.m_bsx;
            double qy = qy_frac + i * m_sbase.m_asy + j * m_sbase.m_bsy;
            result += interferenceAtOneRecLatticePoint(qx, qy, 0.0);
        }
    }
    return getParticleDensity()*result;
}

double InterferenceFunction2DLattice::interferenceAtOneRecLatticePoint(
        double qx, double qy, double xi) const
{
    if (!m_decay)
        throw Exceptions::NullPointerException(
            "InterferenceFunction2DLattice::interferenceAtOneRecLatticePoint"
            " -> Error! No decay function defined.");
    double qp1, qp2;
    double gamma = xi + m_decay->gamma();
    double delta = m_decay->delta();
    transformToPrincipalAxes(qx, qy, gamma, delta, qp1, qp2);
    return m_decay->evaluate(qp1, qp2);
}

void InterferenceFunction2DLattice::transformToPrincipalAxes(
    double qx, double qy, double gamma, double delta, double &q_pa_1, double &q_pa_2) const
{
    q_pa_1 = qx * std::cos(gamma) + qy * std::sin(gamma);
    q_pa_2 = qx * std::cos(gamma + delta) + qy * std::sin(gamma + delta);
}

void InterferenceFunction2DLattice::calculateReciprocalVectorFraction(
    double qx, double qy, double xi, double &qx_frac, double &qy_frac) const
{
    double a = m_lattice->length1();
    double b = m_lattice->length2();
    double alpha = m_lattice->latticeAngle();
    double qx_rot =  qx*std::cos(xi) + qy*std::sin(xi);
    double qy_rot = -qx*std::sin(xi) + qy*std::cos(xi);

    int qa_int = static_cast<int>(std::lround(a*qx_rot / M_TWOPI));
    int qb_int = static_cast<int>(
                     std::lround(b*(qx*std::cos(alpha) + qy*std::sin(alpha)) / M_TWOPI));
    qx_frac = qx_rot - qa_int * m_sbase.m_asx - qb_int * m_sbase.m_bsx;
    qy_frac = qy_rot - qa_int * m_sbase.m_asy - qb_int * m_sbase.m_bsy;
}

void InterferenceFunction2DLattice::initialize_rec_vectors()
{
    if(!m_lattice)
        throw std::runtime_error("InterferenceFunction2DLattice::initialize_rec_vectors() -> "
                                 "Error. No lattice defined yet");

    BasicLattice base_lattice(m_lattice->length1(), m_lattice->length2(),
                              m_lattice->latticeAngle());
    m_sbase = base_lattice.reciprocalBases();
}

void InterferenceFunction2DLattice::initialize_calc_factors()
{
    if (!m_decay)
        throw Exceptions::NullPointerException(
            "InterferenceFunction2DLattice::initialize_calc_factors"
            " -> Error! No decay function defined.");

    // number of reciprocal lattice points to use
    double qa_max(0.0), qb_max(0.0);

    m_decay->transformToStarBasis(nmax / m_decay->decayLengthX(),
                                  nmax / m_decay->decayLengthY(),
                                  m_lattice->latticeAngle(), m_lattice->length1(),
                                  m_lattice->length2(), qa_max, qb_max);
    m_na = static_cast<int>(std::lround(std::abs(qa_max)));
    m_nb = static_cast<int>(std::lround(std::abs(qb_max)));
}
