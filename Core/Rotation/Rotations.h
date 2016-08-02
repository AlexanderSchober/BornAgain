// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Rotation/Rotations.h
//! @brief     Declares IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROTATIONS_H
#define ROTATIONS_H

#include "ISample.h" // inheriting from
#include "Transform3D.h"

//! @class IRotation
//! @ingroup samples
//! @brief An interface for classes representing a rotation

//! must be subclass of sample, because it can be registered as a child in ICompositeSample

class BA_CORE_API_ IRotation : public ISample
{
public:
    static IRotation* createRotation(const Geometry::Transform3D& transform);
    virtual ~IRotation() {}

    virtual IRotation* clone() const=0;
    //! Returns a clone with inverted magnetic fields
    virtual IRotation* cloneInvertB() const=0;
    //! Returns a new IRotation object that is the current object's inverse
    virtual IRotation* createInverse() const=0;

    //! Calls the ISampleVisitor's visit method
    void accept(class ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Returns transformation.
    virtual Geometry::Transform3D getTransform3D() const=0;

    //! Returns true if roation matrix is identity matrix (no rotations)
    virtual bool isIdentity() const;
};

BA_CORE_API_ IRotation* CreateProduct(const IRotation& left, const IRotation& right);

class BA_CORE_API_ RotationX : public IRotation
{
public:
    RotationX(double angle);

    RotationX* clone() const { return new RotationX(m_angle); }
    RotationX* cloneInvertB() const { return clone(); }
    RotationX* createInverse() const { return new RotationX(-m_angle); }

    void accept(class ISampleVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Geometry::Transform3D getTransform3D() const;

protected:
    double m_angle;
};

class BA_CORE_API_ RotationY : public IRotation
{
public:
    RotationY(double angle);

    RotationY* clone() const { return new RotationY(m_angle); }
    RotationY* cloneInvertB() const { return clone(); }
    RotationY* createInverse() const { return new RotationY(-m_angle); }

    void accept(class ISampleVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Geometry::Transform3D getTransform3D() const;

protected:
    double m_angle;
};

class BA_CORE_API_ RotationZ : public IRotation
{
public:
    RotationZ(double angle = 0.0);

    RotationZ* clone() const { return new RotationZ(m_angle); }
    RotationZ* cloneInvertB() const { return clone(); }
    RotationZ* createInverse() const { return new RotationZ(-m_angle); }

    void accept(class ISampleVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Geometry::Transform3D getTransform3D() const;

protected:
    double m_angle;
};

class BA_CORE_API_ RotationEuler : public IRotation
{
public:
    RotationEuler(double alpha, double beta, double gamma);

    RotationEuler* clone() const { return new RotationEuler(m_alpha, m_beta, m_gamma); }
    RotationEuler* cloneInvertB() const { return clone(); }
    IRotation* createInverse() const;

    void accept(class ISampleVisitor* visitor) const { visitor->visit(this); }

    double getAlpha() const { return m_alpha; }
    double getBeta() const { return m_beta; }
    double getGamma() const { return m_gamma; }

    Geometry::Transform3D getTransform3D() const;

protected:
    double m_alpha, m_beta, m_gamma;
};

#endif // ROTATIONS_H
