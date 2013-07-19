#include "IsGISAXS04Builder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "FTDistributions.h"

IsGISAXS04Para1DBuilder::IsGISAXS04Para1DBuilder()
    : m_corr_peak_distance(20.0*Units::nanometer)
    , m_corr_width(7*Units::nanometer)
    , m_corr_length(1e3*Units::nanometer)
    , m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
{
    init_parameters();
}

void IsGISAXS04Para1DBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("corr_peak_distance", &m_corr_peak_distance);
    registerParameter("corr_width", &m_corr_width);
    registerParameter("corr_length", &m_corr_length);
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_raduis", &m_cylinder_radius);
}

ISample *IsGISAXS04Para1DBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(m_corr_peak_distance,m_corr_width, m_corr_length);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer->addLayer(air_layer_decorator);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
//

IsGISAXS04Para2DBuilder::IsGISAXS04Para2DBuilder()
    : m_peak_distance(20.0*Units::nanometer)
    , m_corr_length(0.0)
    , m_domain_size_1(20.0*Units::micrometer)
    , m_domain_size_2(20.0*Units::micrometer)
    , m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
{
    init_parameters();
}

void IsGISAXS04Para2DBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("m_peak_distance", &m_peak_distance);
    registerParameter("m_corr_length", &m_corr_length);
    registerParameter("m_domain_size_1", &m_domain_size_1);
    registerParameter("m_domain_size_2", &m_domain_size_2);
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_raduis", &m_cylinder_radius);
}


ISample *IsGISAXS04Para2DBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function = InterferenceFunction2DParaCrystal::createHexagonal(m_peak_distance, m_corr_length,
                                                                                                                    m_domain_size_1, m_domain_size_2);
    FTDistribution2DCauchy pdf(1.0*Units::nanometer, 1.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf, pdf);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer->addLayer(air_layer_decorator);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
