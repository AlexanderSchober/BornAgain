// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFittingModule1.h
//! @brief     Defines class TestFittingModule1.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFITTINGMODULE1_H_
#define TESTFITTINGMODULE1_H_

#include "IApplicationTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "Simulation.h"
#include "ISampleBuilder.h"

class FitSuite;

//! Test of fitting module with simple samples.

class TestFittingModule1 : public IApplicationTest
{
public:
    TestFittingModule1();
    virtual ~TestFittingModule1();
    virtual void execute();

private:
    //! Initializes sample: layer + nanoparticles, 2 parameters
    void initializeSample1();
    //! Initializes sample: layer + substrate + nanoparticles, 4 parameters
    void initializeSample2();

    void initializeSimulation();
    void initializeRealData();

    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulated_data;
    Simulation *mp_simulation;
    ISample *mp_sample;
    FitSuite *m_fitSuite;
};

#endif /* TESTFITTINGMODULE1_H_ */


