#include "SampleFactory.h"
#include "Exceptions.h"
#include "StandardSamples.h"

#include <iostream>


SampleFactory::SampleFactory()
{
    setOwnObjects(true);

    // samples used for fresnel coefficients validation
    registerItem("AirOnSubstrate", StandardSamples::AirOnSubstrate);
    registerItem("SubstrateOnSubstrate", StandardSamples::SubstrateOnSubstrate);
    registerItem("SimpleMultilayer", StandardSamples::SimpleMultilayer);

    // samples used for offspecular reflectivity validation

    //10x2 layers for comparison of diffuse (off-specular) reflectivity with and without cross-correlation in layer's roughnesses
    registerItem("MultilayerOffspecTestcase1a", StandardSamples::MultilayerOffspecTestcase1a);
    registerItem("MultilayerOffspecTestcase1b", StandardSamples::MultilayerOffspecTestcase1b);

    // thin layer of air (two different thicknesses) to check diffuse (off-specular) reflectivity
    registerItem("MultilayerOffspecTestcase2a", StandardSamples::MultilayerOffspecTestcase2a);
    registerItem("MultilayerOffspecTestcase2b", StandardSamples::MultilayerOffspecTestcase2b);

    // rotated pytamid from IsGISAXS9 example
    registerItem("IsGISAXS9_RotatedPyramid", StandardSamples::IsGISAXS9_RotatedPyramid);

    // mesocrystal
    registerItem("MesoCrystal1", StandardSamples::MesoCrystal1);
}

