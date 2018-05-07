// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootResidualFunction.h
//! @brief     Declares class RootResidualFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROOTRESIDUALFUNCTION_H
#define ROOTRESIDUALFUNCTION_H

#include "KernelTypes.h"

#ifdef _WIN32
#include "Math/FitMethodFunction.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/FitMethodFunction.h"
#pragma GCC diagnostic pop
#endif

//! Minimizer function with access to single data element residuals,
//! required by Fumili, Fumili2 and GSLMultiMin minimizers.

class RootResidualFunction : public ROOT::Math::FitMethodFunction
{
public:
    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t Type_t;

    RootResidualFunction(gradient_function_t fun_gradient, size_t npars, size_t ndatasize);

    Type_t Type() const;

    ROOT::Math::IMultiGenFunction* Clone() const;

    //! evaluation of single data element residual
    double DataElement(const double* pars, unsigned int i_data, double* gradient = 0) const;

private:
    //! evaluation of chi2
    double DoEval(const double* pars) const;

    size_t m_npars;
    size_t m_datasize;
    gradient_function_t m_fun_gradient;
};

#endif //  ROOTRESIDUALFUNCTION_H
