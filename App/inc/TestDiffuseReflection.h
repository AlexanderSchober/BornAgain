// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestDiffuseReflection.h
//! @brief     Defines class TestDiffuseReflection.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTDIFFUSEREFLECTION_H
#define TESTDIFFUSEREFLECTION_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "TH2D.h"

class MultiLayer;

//! Test diffuse (off-specular) reflection from multilayer.

class TestDiffuseReflection : public IFunctionalTest
{
 public:
    TestDiffuseReflection();

    void execute();

    void draw();

 private:
    MultiLayer *m_sample; //!< pointer to multilayer sample
    OutputData<double  > *m_data_spec; //!< specular reflectivity
    OutputData<double  > *m_data_offspec; //!< off-specular reflectivity

    double m_alphaMin; //!< min alpha value
    double m_alphaMax; //!< max alpha value
    int m_npoints;     //!< number of points in range [m_alphaMin, m_alphaMax]

};

#endif // TESTDIFFUSESCATTERING_H


