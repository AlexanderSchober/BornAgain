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

#include "FunctionalTestRegistry.h"
#include "FunctionalMultiTest.h"
#include "CoreFunctionalTestComponentService.h"

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

    CoreFunctionalTestComponentService service(info);
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
