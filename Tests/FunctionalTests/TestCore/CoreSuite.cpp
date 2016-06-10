// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/core_functional_test.h
//! @brief     Implements program CoreSuite, to run core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FutestSuite.h"
#include "FunctionalTestRegistry.h"
#include "FunctionalMultiTest.h"
#include "CoreFunctionalTest.h"

//! Program CoreSuite, to run core functional tests.
int main(int argc, char** argv)
{
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);

    const FunctionalTestInfo* info =
        FunctionalTestRegistry::instance().getItemOrExplain(test_name, "CoreSuite");
    if( !info )
        return 1;

    FutestSuite service(info, [] (const FutestSuite* s) -> IFunctionalTest* {
            return new CoreFunctionalTest(
        s->getTestName(), s->getTestDescription(), s->getSimulation(),
        s->getReferenceData(), s->getTestThreshold(), s->getReferenceFileName()); } );
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
