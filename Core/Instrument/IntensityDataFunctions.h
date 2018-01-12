// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IntensityDataFunctions.h
//! @brief     Defines class IntensityDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTENSITYDATAFUNCTIONS_H
#define INTENSITYDATAFUNCTIONS_H

#include <memory>
#include "OutputData.h"

class IHistogram;
class IResolutionFunction2D;

//! Functions to work with intensity data.
//! @ingroup tools

namespace IntensityDataFunctions {

//! Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]).
BA_CORE_API_ double getRelativeDifference(
    const OutputData<double>& dat, const OutputData<double>& ref);

BA_CORE_API_ double getRelativeDifference(const IHistogram& dat, const IHistogram& ref);

BA_CORE_API_ OutputData<double>* createRelativeDifferenceData(
    const OutputData<double>& data, const OutputData<double>& reference);

#ifndef SWIG
//! Returns a pointer to new object with input data rotated by
//! n*90 deg counterclockwise (n > 0) or clockwise (n < 0)
//! Axes are swapped if the data is effectively rotated by 90 or 270 degrees
//! Applicable to 2D arrays only
BA_CORE_API_ std::unique_ptr<OutputData<double>>
createRearrangedDataSet(const OutputData<double>& data, int n);
#endif //SWIG

//! Returns new IntensityData objects which axes clipped to represent the specified rectangle.
BA_CORE_API_ OutputData<double>* createClippedDataSet(
    const OutputData<double>& origin, double x1, double y1, double x2, double y2);

//! Applies detector resolution function and returns new IntensityData object.
BA_CORE_API_ OutputData<double>* applyDetectorResolution(
    const OutputData<double>& origin, const IResolutionFunction2D& resolution_function);

//! Transforms coordinate on axis into the bin-fraction-coordinate.
BA_CORE_API_ double coordinateToBinf(double coordinate, const IAxis& axis);

//! Transforms bin-fraction-coordinate into axis coordinate.
BA_CORE_API_ double coordinateFromBinf(double value, const IAxis& axis);

//! Transforms x,y coordinate from OutputData axes coordinates to bin-fraction-coordinates.
BA_CORE_API_ void coordinateToBinf(double& x, double& y, const OutputData<double>& data);

//! Transforms x,y coordinate from bin-fraction-coordinates to OutputData's axes coordinates.
BA_CORE_API_ void coordinateFromBinf(double& x, double& y, const OutputData<double>& data);

//! Creates a vector of vectors of double (2D Array) from OutputData.
BA_CORE_API_ std::vector<std::vector<double>> create2DArrayfromOutputData(
        const OutputData<double>& data);

//! Creates a Fourier Transform of a 2D Array (vector of vectors).
BA_CORE_API_ std::vector<std::vector<double>> FT2DArray(
        const std::vector<std::vector<double>>& signal);

//! Creates OutputData from a 2D Array.
BA_CORE_API_ OutputData<double>* createOutputDatafrom2DArray(
        const std::vector<std::vector<double>>& array_2d);

// Another way of creating OutputData from a 2D Array
BA_CORE_API_ OutputData<double>* createOutputDatafrom2DArrayV2(
        const std::vector<std::vector<double>>& array_2d, const OutputData<double>& reference);

//! Creates Fourier Transform (OutputData format) of intensity map (OutputData format).
BA_CORE_API_ OutputData<double>* getFourierTransform(const OutputData<double> &data);

}; // namespace IntensityDataFunctions

#endif // INTENSITYDATAFUNCTIONS_H
