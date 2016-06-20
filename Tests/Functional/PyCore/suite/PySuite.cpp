// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PySuite.cpp
//! @brief     Implements program PySuite, to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestSuite.h"
#include "PySuiteTest.h"

class PySuite : public FunctionalTestSuite
{
public:
    PySuite() { setName("PySuite"); }
    IFunctionalTest* getTest() const { return new PySuiteTest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! The main function of PySuite, to run functional tests
int main(int argc, char** argv)
{
    return PySuite().execute(argc, argv);
}
