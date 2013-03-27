// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Lattice.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef LATTICE_H_
#define LATTICE_H_

#include "Types.h"
#include "ISelectionRule.h"
#include "TRange.h"
#include "FastVector.h"

#include <vector>

//! A Lattice with three basis vectors.

class Lattice
{
 public:
    Lattice();
    Lattice(const kvector_t& a1, const kvector_t& a2, const kvector_t& a3);
    Lattice(const Lattice& lattice);
    ~Lattice();

    //! Initializes cached data
    void initialize() const;

    //! Returns basis vector a
    kvector_t getBasisVectorA() const { return m_a1; }

    //! Returns basis vector b
    kvector_t getBasisVectorB() const { return m_a2; }

    //! Returns basis vector c
    kvector_t getBasisVectorC() const { return m_a3; }

    //! Returns the volume of the unit cell
    double getVolume() const;

    //! Returns the reciprocal basis vectors
    void getReciprocalLatticeBasis(kvector_t& b1, kvector_t& b2, kvector_t& b3) const;

    //! Returns the nearest lattice point from a given vector
    IndexVector3D getNearestLatticeVectorCoordinates(const kvector_t& vector_in) const;

    //! Returns the nearest reciprocal lattice point from a given vector
    IndexVector3D getNearestReciprocalLatticeVectorCoordinates(const kvector_t& vector_in) const;

    //! Returns a list of lattice vectors within a specified distance of a given vector
//    std::vector<kvector_t> getLatticeVectorsWithinRadius(
//            const kvector_t& input_vector, double radius) const;

    //! Returns a list of reciprocal lattice vectors within a specified distance of a given vector
//    std::vector<kvector_t> getReciprocalLatticeVectorsWithinRadius(
//            const kvector_t& input_vector, double radius) const;
    void computeReciprocalLatticeVectorsWithinRadius(
            const kvector_t& input_vector, double radius) const;


    //! Returns a list of rotation angles within a specified range that hit a maximal set of small Bragg peaks
    //std::vector<double> collectBraggAngles(size_t size, double max_radius, const TRange<double>& phi_range, const TRange<double>& z_range) const;
    std::vector<double> collectBraggAngles(size_t size, double max_radius, const TRange<double>& phi_range, const TRange<double>& z_range) const;

    //! Sets a selection rule for the reciprocal vectors
//    void setSelectionRule(ISelectionRule *p_selection_rule) {
//        if (mp_selection_rule != p_selection_rule) {
//            delete mp_selection_rule;
//            mp_selection_rule = p_selection_rule;
//        }
//    }
    void setSelectionRule(const ISelectionRule& p_selection_rule) {
        delete mp_selection_rule;
        mp_selection_rule = p_selection_rule.clone();
    }

    static Lattice createFCCLattice(double a);

    static Lattice createTrigonalLattice(double a, double c);

    const KVectorContainer& getKVectorContainer() const { return m_kvector_container; }
 private:
    Lattice& operator=(const Lattice& lattice);
//    std::vector<kvector_t> getVectorsWithinRadius(const kvector_t& input_vector,
//            const IndexVector3D& nearest_coords, double radius,
//            const kvector_t& v1, const kvector_t& v2, const kvector_t& v3,
//            const kvector_t& rec1, const kvector_t& rec2, const kvector_t& rec3) const;

    void computeVectorsWithinRadius(const kvector_t& input_vector,
            const IndexVector3D& nearest_coords, double radius,
            const kvector_t& v1, const kvector_t& v2, const kvector_t& v3,
            const kvector_t& rec1, const kvector_t& rec2, const kvector_t& rec3) const;

    void computeReciprocalVectors() const;
    void computeInverseLatticeVectors() const;
    void computeInverseReciprocalLatticeVectors() const;
    static void computeInverseVectors(const kvector_t& v1, const kvector_t& v2, const kvector_t& v3, kvector_t& o1, kvector_t& o2, kvector_t& o3);
    ISelectionRule *mp_selection_rule;
    kvector_t m_a1, m_a2, m_a3; //!< Basis vectors in real space
    mutable kvector_t m_b1, m_b2, m_b3; //!< Cache of basis vectors in reciprocal space
    mutable kvector_t m_amin1, m_amin2, m_amin3, m_bmin1, m_bmin2, m_bmin3; //!< Cache of inverse vectors for calculation of coordinates
    mutable bool m_cache_ok, m_is_zero; //!< Boolean indicating if the reciprocal vectors are already initialized in the cache

    mutable KVectorContainer m_kvector_container;
};

#endif /* LATTICE_H_ */
