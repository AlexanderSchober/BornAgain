// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/buffer.h
//! @brief     Defines Buffer class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_BUFFER_H
#define BA3D_BUFFER_H

#include "../def.h"
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

namespace ba3d {
//------------------------------------------------------------------------------

class Geometry;

// GL buffer
class Buffer final : protected QOpenGLFunctions {
public:
  Buffer(Geometry const&);
  void draw();

private:
  int vertexCount;
  QOpenGLVertexArrayObject vao; QOpenGLBuffer glBuffer;
};

//------------------------------------------------------------------------------
}
#endif
