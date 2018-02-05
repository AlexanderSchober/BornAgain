// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/camera.cpp
//! @brief     Implements Camera class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "camera.h"

namespace ba3d {
//------------------------------------------------------------------------------

Camera::Camera()
: pos(xyz::_z, xyz::_0, xyz::_x), zoom(1)
, vertAngle(60), nearPlane(1), farPlane(10000)
, lightPos(pos.eye), lightPosRotated(lightPos) {
  setAspectRatio(1);
}

Camera::pos_t::pos_t() : eye(), ctr(), up() {
}

Camera::pos_t::pos_t(const xyz& eye_, const xyz& ctr_, const xyz& up_,
                     QQuaternion const& rot_)
  : eye(eye_), ctr(ctr_), up(up_), rot(rot_) {
}

Camera::pos_t Camera::pos_t::interpolateTo(rc to, float r) const {
  return pos_t(
    eye.interpolateTo(to.eye, r),
    ctr.interpolateTo(to.ctr, r),
    up.interpolateTo(to.up, r),
    QQuaternion::slerp(rot, to.rot, r)
  );
}

void Camera::lookAt(pos_t::rc pos_) {
  pos = pos_; lightPos = pos.eye;
  set();
}

// recalculate dependent params
void Camera::set() {
  matModel.setToIdentity();
  matModel.lookAt((pos.eye-pos.ctr)*zoom + pos.ctr, pos.ctr, pos.up);

  QQuaternion rt(pos.rot * addRot);
  matModel.translate(+pos.ctr);
  matModel.rotate(rt);
  matModel.translate(-pos.ctr);

  lightPosRotated = rt.inverted().rotatedVector(lightPos);

  emit updated(*this);
}

void Camera::setAspectRatio(float ratio) {
  matProj.setToIdentity();
  matProj.perspective(vertAngle, ratio, nearPlane, farPlane);
}

void Camera::turnBy(QQuaternion const& rot) {
  addRot = rot;
  set();
}

void Camera::zoomBy(float zoom_) {
  zoom = zoom_;
  set();
}

void Camera::endTransform(bool keep) {
  if (keep) {
    pos.rot = (pos.rot * addRot).normalized();
    pos.eye = pos.eye * zoom; // TODO limit
  }

  addRot = QQuaternion();
  zoom = 1;

  set();
}

//------------------------------------------------------------------------------
}
