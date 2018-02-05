// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/demo/demo_model.h
//! @brief     Defines DemoModel class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_DEMOMODEL_H
#define BA3D_DEMOMODEL_H

#include <ba3d/model/model.h>
#include <ba3d/model/particles.h>
#include "lattice.h"
#include <QAtomicInteger>

//------------------------------------------------------------------------------

class DemoModel : public ba3d::Model {
public:
  using super = ba3d::Model;

  using xyz = ba3d::xyz;
  using Particle = ba3d::particle::Particle;
  using Camera   = ba3d::Camera;

  DemoModel();

  void switchBack();
  void switchFront();
  void switchOne();

  void square(float sigma);
  void one();
  void oneOut();
  void oneIn(ba3d::particle::kind);

  void setCameraTop(bool animate = false);
  void setCameraSide(bool animate = false);
  void setCameraOne(bool animate = false);

  void setCamera(Camera::pos_t::rc, bool animate = false);

  void cameraUpdated(Camera const&);

private:
  void addSubstrate();
  void addLayer();

  enum {backNONE,  backSUBSTRATE, backLAYER }           back  = backNONE;
  enum {frontNONE, frontONE, frontSQUARELOW,
                   frontSQUAREHIGH, frontSQUAREINSANE } front = frontNONE;

  float szSample = 400;
  float const spacing  = 20; // of particles
  float const R = 6;
  float const hgtLayer = 20, hgtSubstrate = 35;

  Camera::pos_t camPos;

private:
  void addLayer(ba3d::dr, QColor);

  QVector<Particle*> ps;
  Particle* p; ba3d::particle::kind kind = ba3d::particle::kind::None;

  Lattice activeMesh;

private:
  void snooze(bool withEye);
};

//------------------------------------------------------------------------------
#endif
