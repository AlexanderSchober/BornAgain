// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/BatchSimulation.h
//! @brief     Defines BatchSimulation class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BATCHSIMULATION_H
#define BATCHSIMULATION_H

#include "IFunctionalTest.h"

//! Special test for simulation running in batch mode.

class BatchSimulation : public IFunctionalTest {
protected:
    bool runTest();
};

#endif

