// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/StandardFits/RectDetectorFitTest.h
//! @brief     Declares class RectDetectorFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTDETECTORFITTEST_H
#define RECTDETECTORFITTEST_H

#include "IMinimizerTest.h" // inheriting from


//! @class RectDetectorFitTest
//! @ingroup standard_samples
//! @brief Fit of simulation with rectangular detector. The detector is cropped, masks are applied.

class RectDetectorFitTest : public IMinimizerTest
{
public:
    RectDetectorFitTest();

protected:
    virtual std::unique_ptr<GISASSimulation> createSimulation();
    virtual std::unique_ptr<OutputData<double> > createOutputData(const GISASSimulation *simulation);

};

#endif // RECTDETECTORFITTEST_H
