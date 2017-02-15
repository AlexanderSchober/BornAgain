// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/IShape.cpp
//! @brief     Implements default methods of interface IShape.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IShape.h"


std::vector<kvector_t> IShape::vertices() const
{
    return m_vertices;
}

std::vector<kvector_t> RectangleVertices(double length, double width, double z)
{
    std::vector<kvector_t> result(4);
    result[0] = kvector_t(length/2.0, width/2.0, z);
    result[1] = kvector_t(-length/2.0, width/2.0, z);
    result[2] = kvector_t(-length/2.0, -width/2.0, z);
    result[3] = kvector_t(length/2.0, -width/2.0, z);
    return result;
}
