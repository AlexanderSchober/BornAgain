// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IntensityDataFunctions.h
//! @brief     Defines class IntensityDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAFUNCTIONS_H
#define INTENSITYDATAFUNCTIONS_H

#include "OutputData.h"
class IResolutionFunction2D;
class IHistogram;

//! @class IntensityDataFunctions
//! @ingroup tools
//! @brief Class holding collection of static methods to work with intensity data.

namespace IntensityDataFunctions {
double getRelativeDifference(const OutputData<double> &dat,
                             const OutputData<double> &ref);

double getRelativeDifference(const IHistogram &dat, const IHistogram &ref);

OutputData<double> *
createRelativeDifferenceData(const OutputData<double> &data,
                             const OutputData<double> &reference);

//! Returns new IntensityData objects which axes clipped to represent the
//! specified rectangle
OutputData<double> *createClippedDataSet(const OutputData<double> &origin,
                                         double x1, double y1, double x2,
                                         double y2);

//! Applies detector resolution function and returns new IntensityData object
OutputData<double> *
applyDetectorResolution(const OutputData<double> &origin,
                        const IResolutionFunction2D &resolution_function);

//! Transforms coordinate on axis into the bin-fraction-coordinate.
double coordinateToBinf(double coordinate, const IAxis &axis);

//! Transforms bin-fraction-coordinate into axis coordinate.
double coordinateFromBinf(double value, const IAxis &axis);

//! Transform x,y coordinate from OutputData axes coordinates to
//! bin-fraction-coordinates
void coordinateToBinf(double &x, double &y, const OutputData<double> &data);

//! Transform x,y coordinate from bin-fraction-coordinates to OutputData's axes
//! coordinates
void coordinateFromBinf(double &x, double &y, const OutputData<double> &data);
};

#endif // INTENSITYDATAFUNCTIONS_H
