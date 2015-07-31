// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Particle.cpp
//! @brief     Implements class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Particle.h"
#include "Materials.h"
#include "FormFactorDecoratorPositionFactor.h"

#include <boost/scoped_ptr.hpp>

Particle::Particle()
{
    setName("Particle");
    registerParameter("position_x", &m_position[0]);
    registerParameter("position_y", &m_position[1]);
    registerParameter("position_z", &m_position[2]);
}

Particle::Particle(const IMaterial &p_material)
    : mP_material(p_material.clone())
{
    setName("Particle");
    registerParameter("position_x", &m_position[0]);
    registerParameter("position_y", &m_position[1]);
    registerParameter("position_z", &m_position[2]);
}

Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor)
    : mP_material(p_material.clone())
    , mP_form_factor(form_factor.clone())
{
    setName("Particle");
    registerParameter("position_x", &m_position[0]);
    registerParameter("position_y", &m_position[1]);
    registerParameter("position_z", &m_position[2]);
    registerChild(mP_form_factor.get());
}

Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor,
                   const IRotation &rotation)
    : mP_material(p_material.clone())
    , mP_form_factor(form_factor.clone())
{
    setName("Particle");
    registerParameter("position_x", &m_position[0]);
    registerParameter("position_y", &m_position[1]);
    registerParameter("position_z", &m_position[2]);
    setRotation(rotation);
    registerChild(mP_form_factor.get());
}

Particle::~Particle()
{
}

Particle *Particle::clone() const
{
    Particle *p_result = new Particle();

    if (mP_form_factor.get())
        p_result->setFormFactor(*mP_form_factor);
    if (mP_material.get())
        p_result->setMaterial(*mP_material);
    if (mP_ambient_material.get())
        p_result->setAmbientMaterial(*mP_ambient_material);
    if (mP_rotation.get())
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    p_result->setName(getName());

    return p_result;
}

Particle *Particle::cloneInvertB() const
{
    Particle *p_result = new Particle();
    if (mP_form_factor.get())
        p_result->setFormFactor(*mP_form_factor);

    if (mP_material.get())
        p_result->mP_material.reset(Materials::createInvertedMaterial(mP_material.get()));
    if (mP_ambient_material.get())
        p_result->mP_ambient_material.reset(
            Materials::createInvertedMaterial(mP_ambient_material.get()));

    if (mP_rotation.get())
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);

    p_result->setName(getName() + "_inv");
    return p_result;
}

IFormFactor *Particle::createTransformedFormFactor(complex_t wavevector_scattering_factor,
    const IRotation *p_rotation, kvector_t translation) const
{
    if (!mP_form_factor.get()) return 0;
    boost::scoped_ptr<IRotation> P_total_rotation(createComposedRotation(p_rotation));
    kvector_t total_position = getComposedTranslation(p_rotation, translation);
    boost::scoped_ptr<IFormFactor> P_temp_ff1;
    if (P_total_rotation.get()) {
        P_temp_ff1.reset(new FormFactorDecoratorRotation(*mP_form_factor, *P_total_rotation));
    } else {
        P_temp_ff1.reset(mP_form_factor->clone());
    }
    boost::scoped_ptr<IFormFactor> P_temp_ff2;
    if (total_position != kvector_t()) {
        P_temp_ff2.reset(new FormFactorDecoratorPositionFactor(*P_temp_ff1, total_position));
    } else {
        P_temp_ff2.swap(P_temp_ff1);
    }
    FormFactorDecoratorMaterial *p_ff
        = new FormFactorDecoratorMaterial(*P_temp_ff2, wavevector_scattering_factor);
    if (mP_material.get()) {
        if (mP_rotation.get()) {
            boost::scoped_ptr<const IMaterial> P_transformed_material(
                        mP_material->createTransformedMaterial(*P_total_rotation));
            p_ff->setMaterial(*P_transformed_material);
        } else {
            p_ff->setMaterial(*mP_material);
        }
    }
    if (mP_ambient_material.get()) p_ff->setAmbientMaterial(*mP_ambient_material);
    return p_ff;
}

void Particle::setFormFactor(const IFormFactor &form_factor)
{
    if (&form_factor != mP_form_factor.get()) {
        if (mP_form_factor.get()) deregisterChild(mP_form_factor.get());
        mP_form_factor.reset(form_factor.clone());
        registerChild(mP_form_factor.get());
    }
}
