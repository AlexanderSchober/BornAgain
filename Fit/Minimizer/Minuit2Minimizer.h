// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Minuit2Minimizer.h
//! @brief     Declares class Minuit2Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINUIT2MINIMIZER_H
#define MINUIT2MINIMIZER_H

#include "BasicMinimizer.h"

//! @class Minuit2Minimizer
//! @ingroup fitting_internal
//! @brief The Minuit2Minimizer class is a wrapper for ROOT Minuit2 minimizer
//! See Minuit2 user manual https://root.cern.ch/root/htmldoc/guides/minuit2/Minuit2.pdf.

class BA_CORE_API_ Minuit2Minimizer : public BasicMinimizer
{
public:
    Minuit2Minimizer();

    //! Sets minimization strategy (0-low, 1-medium, 2-high minimization quality).
    //! At low quality number of function calls will be economized. Default value is 1.
    void setStrategy(int value);

    //! Sets error definition factor for parameter error calculation.
    //! If objective function (OF) is the usual chisquare function and if the user wants the usual
    //! one-standard-deviation errors, then the error definition should be 1.0. If OF is a
    //! negative-log-likelihood function, then 0.5. If OF is a chisquare, but the user wants
    //! two-standard-deviation errors, 4.0.
    //! Default value is 1.0
    void setErrorDefinition(double value);

    //!< Sets tolerance on the function value at the minimum.
    //!< Minimization will stop when the estimated vertical distance to the minimum (EDM) is less
    //! than 0.001*tolerance*ErrorDef. Here ErrorDef=1 for chi squared fit and ErrorDef=0.5
    //! for negative log likelihood fit.
    //! Default value is 0.01
    void setTolerance(double value);

    //!< Sets relative floating point arithmetic precision.
    //!< Should be adjusted when the user knows that objectiove function value is not
    //!< calculated to the nominal machine accuracy. Typical values are between 10^-5 and 10^-14.
    //!  Default value is -1.0 (minimizer specific will be used).
    void setPrecision(double value);

    //! Sets minimizer internal print level.
    //! Default value is 0 (silent).
    void setPrintLevel(int value);

private:

};

#endif
