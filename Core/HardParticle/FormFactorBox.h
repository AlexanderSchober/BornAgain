// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBox.h
//! @brief     Declares class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORBOX_H
#define FORMFACTORBOX_H

#include "IFormFactorBorn.h" // inheriting from

//! @class FormFactorBox
//! @ingroup formfactors
//! @brief The formfactor for a rectangular box.

class BA_CORE_API_ FormFactorBox : public IFormFactorBorn
{
public:
    //! @brief Box constructor
    //! @param length of Box's base
    //! @param width of Box's base
    //! @param height of Box
    FormFactorBox( double length, double width, double height);

    FormFactorBox *clone() const;

    virtual void accept(ISampleVisitor *visitor) const final;

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }

    virtual double getRadialExtension() const final { return m_length/2.0; }

    virtual complex_t evaluate_for_q(const cvector_t q) const final;

protected:
    virtual void init_parameters();

private:
    double m_length;
    double m_width;
    double m_height;
};

#endif // FORMFACTORBOX_H
