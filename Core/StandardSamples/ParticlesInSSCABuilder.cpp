// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParticlesInSSCABuilder.cpp
//! @brief     Implements class ParticlesInSSCABuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticlesInSSCABuilder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "Units.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Distributions.h"
#include "ParticleDistribution.h"


ParticlesInSSCABuilder::ParticlesInSSCABuilder()
{
}

ISample *ParticlesInSSCABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    InterferenceFunctionRadialParaCrystal *p_interference_function =
            new InterferenceFunctionRadialParaCrystal(15.0*Units::nanometer,
                    1e3*Units::nanometer);
    FTDistribution1DGauss pdf(5*Units::nanometer);
    p_interference_function->setProbabilityDistribution(pdf);
    p_interference_function->setKappa(4.02698);
    ParticleLayout particle_layout;

    FormFactorCylinder ff_cylinder(5.0*Units::nanometer, 5.0*Units::nanometer);
    Particle particle_prototype(particle_material, ff_cylinder);

    DistributionGaussian gauss(5.0*Units::nanometer, 1.25*Units::nanometer);
    ParameterDistribution par_distr("*/radius", gauss, 30, 3.0);
    par_distr.linkParameter("*/height");
    ParticleDistribution particle_collection(particle_prototype, par_distr);
    particle_layout.addParticle(particle_collection);

    particle_layout.addInterferenceFunction(p_interference_function);
    particle_layout.setApproximation(ILayout::SSCA);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    return multi_layer;
}
