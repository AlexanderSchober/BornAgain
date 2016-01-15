// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTetrahedron.h
//! @brief     Defines class FormFactorTetrahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTETRAHEDRON_H
#define FORMFACTORTETRAHEDRON_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorTetrahedron
//! @ingroup formfactors
//! @brief The formfactor of tetrahedron.

class BA_CORE_API_ FormFactorTetrahedron : public IFormFactorBorn
{
public:
    //! @brief Tetrahedron constructor
    //! @param length of a side of Tetrahedron's base
    //! @param height of Tetrahedron
    //! @param angle in radians between base and facet
    FormFactorTetrahedron(double length, double height, double alpha);
    ~FormFactorTetrahedron();

    virtual FormFactorTetrahedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;
    void setHeight(double height);

    double getLength() const;
    void setLength(double length);

    double getAlpha() const;
    void setAlpha(double alpha);

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_height;
    double m_length;
    double m_alpha;
    double m_root3; // Cached value of square root of 3

    // addition integration
    mutable cvector_t m_q;
    complex_t Integrand(double Z, void* params) const;
    MemberComplexFunctionIntegrator<FormFactorTetrahedron> *m_integrator;

};

inline double FormFactorTetrahedron::getHeight() const
{
    return m_height;
}

inline void FormFactorTetrahedron::setHeight(double height)
{
    m_height = height;
}

inline double FormFactorTetrahedron::getLength() const
{
    return m_length;
}

inline void FormFactorTetrahedron::setLength(double length)
{
    m_length = length;
}

inline double FormFactorTetrahedron::getAlpha() const
{
    return m_alpha;
}

inline void FormFactorTetrahedron::setAlpha(double alpha)
{
    m_alpha = alpha;
}

#endif // FORMFACTORTETRAHEDRON_H
