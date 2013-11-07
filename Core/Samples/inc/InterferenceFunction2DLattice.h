// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunction2DLattice.h
//! @brief     Defines class InterferenceFunction2DLattice.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DLATTICE_H_
#define INTERFERENCEFUNCTION2DLATTICE_H_

#include "IInterferenceFunction.h"
#include "Lattice2DIFParameters.h"
#include "FTDistributions.h"

//! ?

class BA_CORE_API_ InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DLattice(const Lattice2DIFParameters& lattice_params);
    virtual ~InterferenceFunction2DLattice();

    virtual InterferenceFunction2DLattice *clone() const {
        InterferenceFunction2DLattice *p_clone = new InterferenceFunction2DLattice(m_lattice_params);
        p_clone->setProbabilityDistribution(*mp_pdf);
        return p_clone;
    }

    void setProbabilityDistribution(const IFTDistribution2D& pdf);

    virtual double evaluate(const cvector_t& q) const;
protected:
    //! Returns interference from a single reciprocal lattice vector
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;

    //! Returns reciprocal coordinates in the principal axis system
    void transformToPrincipalAxes(double qx, double qy, double gamma,
            double delta, double& q_pa_1, double& q_pa_2) const;

    //! Returns qx,qy coordinates of q - qint, where qint is a reciprocal lattice vector
    //! bounding the reciprocal unit cell to which q belongs
    void calculateReciprocalVectorFraction(double qx, double qy,
            double& qx_frac, double& qy_frac) const;

    Lattice2DIFParameters m_lattice_params;
    IFTDistribution2D *mp_pdf;
    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday
private:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    //! Initializes the x,y coordinates of the a*,b* reciprocal bases
    void initialize_rec_vectors();

    //! Initializes factors needed in each calculation
    void initialize_calc_factors();

    double m_asx, m_asy; //!< x,y coordinates of a*
    double m_bsx, m_bsy; //!< x,y coordinates of b*
    double m_prefactor; //!< fixed prefactor for normalization
    int m_na, m_nb; //!< determines the number of reciprocal lattice points to use
};

#endif /* INTERFERENCEFUNCTION2DLATTICE_H_ */


