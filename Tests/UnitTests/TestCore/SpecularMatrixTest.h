#ifndef SPECULARMATRIXTEST_H
#define SPECULARMATRIXTEST_H

#include "SpecularMatrix.h"
#include "gtest/gtest.h"

class SpecularMatrixTest : public ::testing :: Test
{
protected:
    SpecularMatrixTest();
    virtual ~SpecularMatrixTest(){}

};

SpecularMatrixTest::SpecularMatrixTest()
{

}

TEST_F(SpecularMatrixTest, initial)
{
    MultiLayer mLayer;
    kvector_t v;
    SpecularMatrix::MultiLayerCoeff_t coeff;
    SpecularMatrix matrix;

    // @Error: Throws exception (Layer index is out of bounds)
    //matrix.execute(mLayer, v, coeff);


    const IMaterial *air = MaterialManager::getHomogeneousMaterial("air",0,1.0);
    Layer layer0(*air, 0*Units::nanometer);
    mLayer.addLayer(layer0);

    matrix.execute(mLayer, v, coeff);

}


#endif //SPECULARMATRIXTEST_H
