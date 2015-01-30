// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestInfLongBox.h
//! @brief     Defines class TestInfLongBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTINFLONGBOX_H
#define TESTINFLONGBOX_H


#include "IApplicationTest.h"
#include "ISampleBuilder.h"

class OffSpecSimulation;

class TestInfLongBox : public IApplicationTest
{
public:
    TestInfLongBox();
    virtual ~TestInfLongBox() { }

    virtual void execute();
	void drawff ();

    //! Sample builder
    class TestSampleBuilder : public ISampleBuilder
    {
    public:
        TestSampleBuilder();
        virtual ISample *buildSample() const;
    protected:
        //! Registers some class members for later access via parameter pool
        virtual void init_parameters();
        double m_w; //width
        double m_h; //heigth
        double m_lattice_length;
        double m_xi;
    };

private:

    //! Initializes simulation
    void initializeSimulation();


    //! plot IsGISAXS data and IsGISAXS fit results
    void save_results();
    void plot_results();


    OffSpecSimulation *mp_simulation;
    SampleBuilder_t mp_sample_builder;
};

#endif // TESTINFLONGBOX_H


