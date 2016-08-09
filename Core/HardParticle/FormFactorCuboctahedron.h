// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCuboctahedron.h
//! @brief     Defines class FormFactorCuboctahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCUBOCTAHEDRON_H
#define FORMFACTORCUBOCTAHEDRON_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorCuboctahedron
//! @ingroup formfactors
//! @brief The formfactor of a cuboctahedron.

class BA_CORE_API_ FormFactorCuboctahedron : public FormFactorPolyhedron
{
public:
    FormFactorCuboctahedron(double length, double height, double height_ratio, double alpha);

    FormFactorCuboctahedron *clone() const final {
        return new FormFactorCuboctahedron(m_length, m_height, m_height_ratio, m_alpha); }
    void accept(ISampleVisitor *visitor) const final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getHeightRatio() const { return m_height_ratio; }
    double getAlpha() const { return m_alpha; }

private:
    static const PolyhedralTopology topology;
    void onChange() final;

    double m_length;
    double m_height;
    double m_height_ratio;
    double m_alpha;
};

#endif // FORMFACTORCUBOCTAHEDRON_H
