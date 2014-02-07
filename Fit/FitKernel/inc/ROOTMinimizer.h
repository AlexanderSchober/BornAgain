// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/ROOTMinimizer.h
//! @brief     Defines class ROOTMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMINIMIZER_H
#define ROOTMINIMIZER_H

#include "IMinimizer.h"
#include "OutputData.h"
#include "Exceptions.h"
#include "ROOTMinimizerFunction.h"
#include "FitSuiteParameters.h"
#include <string>
#include "Math/Minimizer.h"
#include "Math/Functor.h"


//! @class ROOTMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for ROOT minimizers to interface with FitSuite

class BA_CORE_API_ ROOTMinimizer : public IMinimizer
{
 public:
    ROOTMinimizer(const std::string& minimizer_name, const std::string& algo_type=std::string());
    virtual ~ROOTMinimizer();

    virtual void minimize();

    virtual void setParameter(size_t index, const FitParameter *par);

    virtual void setParameters(const FitSuiteParameters& parameters);

    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters);

    virtual void setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize);

    virtual size_t getNumberOfVariables() const { return m_root_minimizer->NDim(); }

    virtual double getMinValue() const { return m_root_minimizer->MinValue(); }

    virtual double getValueOfVariableAtMinimum(size_t i) const {return m_root_minimizer->X()[check_index(i)]; }

    virtual std::vector<double > getValueOfVariablesAtMinimum() const;

    virtual double getErrorOfVariable(size_t i) const { return (m_root_minimizer->Errors() == 0? 0 : m_root_minimizer->Errors()[check_index(i)]); }

    virtual std::vector<double > getErrorOfVariables() const;

    virtual void printResults() const;

    virtual void clear() { m_root_minimizer->Clear(); }

    virtual size_t getNCalls() const;

    //! return minimizer options
    virtual MinimizerOptions &getOptions() { return m_options; }
    virtual const MinimizerOptions &getOptions() const { return m_options; }

    //! set minimizer options
    virtual void setOptions(const MinimizerOptions &options);

    //! Returns created minimizer
    ROOT::Math::Minimizer *getROOTMinimizer() { return m_root_minimizer; }
    const ROOT::Math::Minimizer *getROOTMinimizer() const { return m_root_minimizer; }

    //! Checks if type of algorithm is Levenberg-Marquardt or similar
    virtual bool isGradientBasedAgorithm() { return false;}

    //! return name of the minimizer
    virtual std::string getMinimizerName() const { return m_minimizer_name; }

    //! return name of the minimization algorithm
    virtual std::string getAlgorithmName() const { return m_algo_type; }

 protected:
    virtual void propagateOptions();

    ROOTMinimizer(const ROOTMinimizer& );
    ROOTMinimizer& operator=(const ROOTMinimizer& );

    size_t check_index(size_t index) const { return index<getNumberOfVariables() ? index : throw OutOfBoundsException("ROOTMinimizer::getErrorOfVariable() -> Wrong number of the variable"); }

    std::string m_minimizer_name;
    std::string m_algo_type;
    ROOT::Math::Minimizer *m_root_minimizer;
    ROOTMinimizerChiSquaredFunction *m_chi2_func;
    ROOTMinimizerGradientFunction *m_gradient_func;
    MinimizerOptions m_options;
};

#endif // ROOTMINIMIZER_H
