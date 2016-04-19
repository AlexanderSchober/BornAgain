// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorLongBoxLorentz.h
//! @brief     Defines class FormFactorLongBoxLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLONGBOXLORENTZ_H
#define FORMFACTORLONGBOXLORENTZ_H

#include "IFormFactorBorn.h"

//! @class FormFactorBox
//! @ingroup formfactors
//! @brief The formfactor for a long rectangular box.

class BA_CORE_API_ FormFactorLongBoxLorentz : public IFormFactorBorn
{
public:
    //! @brief Box constructor
    //! @param length of Box's base
    //! @param width of Box's base
    //! @param height of Box
    FormFactorLongBoxLorentz( double length, double width, double height);

    FormFactorLongBoxLorentz *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    //! Returns length of Box
    double getLength() const;

    //! Returns height of Box
    double getHeight() const;

    //! Returns radius of Box
    virtual double getRadius() const;

    //! Returns width of Box
    double getWidth() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_length;
    double m_width;
    double m_height;
};

inline double FormFactorLongBoxLorentz::getLength() const
{
    return m_length;
}

inline double FormFactorLongBoxLorentz::getHeight() const
{
    return m_height;
}

inline double FormFactorLongBoxLorentz::getRadius() const
{
    return m_length/2.0;
}

inline double FormFactorLongBoxLorentz::getWidth() const
{
    return m_width;
}

#endif // FORMFACTORLONGBOXLORENTZ_H


