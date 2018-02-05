// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/truncbox.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshTruncBox(float tD) { // t/D
  if (tD <= 0)
    return meshBox();

  float const D = .5f, t = D * (1 - qMin(tD, 1.f));
  xyz_vec vs; vs.reserve(150);

  QVector<float> as({+D, +t, -t, -D, -D, -t, +t, +D});
  QVector<float> bs({+t, +D, +D, +t, -t, -D, -D, -t});

  auto side = [&](int ax, int ay, int az, int bx, int by, int bz,
                  const xyz& d, bool rev) {
    xyz_vec vs_(8);
    for(int i=0; i<8; ++i)
      vs_[rev ? 7-i : i] =
        xyz(ax*as.at(i) + bx*bs.at(i),
            ay*as.at(i) + by*bs.at(i),
            az*as.at(i) + bz*bs.at(i)) + d;
    vs.addFan(vs_, {0,1,2,3,4,5,6,7,0});
  };

  auto corner = [&](int x, int y, int z) {
    xyz_vec vs_({{D*x,D*y,t*z},{D*x,t*y,D*z},{t*x,D*y,D*z}});
    if (x*y*z > 0)
      vs.addTrig(vs_.at(0), vs_.at(2), vs_.at(1));
    else
      vs.addTrig(vs_.at(0), vs_.at(1), vs_.at(2));
  };

  side(0,1,0, 0,0,1, xyz(+D,0,0), false);
  side(0,1,0, 0,0,1, xyz(-D,0,0), true);
  side(1,0,0, 0,0,1, xyz(0,+D,0), true);
  side(1,0,0, 0,0,1, xyz(0,-D,0), false);
  side(1,0,0, 0,1,0, xyz(0,0,+D), false);
  side(1,0,0, 0,1,0, xyz(0,0,-D), true);

  for (int x : {-1, +1})
    for (int y : {-1, +1})
      for (int z : {-1, +1})
        corner(x, y, z);

  Q_ASSERT(150 == vs.count());

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
