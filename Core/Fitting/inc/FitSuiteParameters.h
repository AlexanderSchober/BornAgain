// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/inc/FitSuiteParameters.h
//! @brief     Defines class FitSuiteParameters.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FITSUITEPARAMETERS_H
#define FITSUITEPARAMETERS_H

#include "Exceptions.h"
#include "SafePointerVector.h"
#include "FitParameterLinked.h"
#include <vector>

class ParameterPool;

//! Holds vector of parameters for FitSuite

class FitSuiteParameters
{
public:
    typedef SafePointerVector<FitParameter > parameters_t;
    typedef parameters_t::iterator iterator;
    typedef parameters_t::const_iterator const_iterator;

    FitSuiteParameters() {}
    virtual ~FitSuiteParameters(){}

    //! clear all defined parameters
    void clear();

    //! add fit parameter
    void addParameter(const std::string &name, double value, double step, const AttLimits &attlim, double error=0.0);

    //! return fit parameter with given name
    const FitParameter *getParameter(const std::string &name) const;
    FitParameter *getParameter(const std::string &name);

    //! set values for all defined parameters
    void setValues(const double *pars_values);
    void setValues(const std::vector<double > &pars_values);

    //! get values of all defined parameters
    std::vector<double > getValues() const;

    //! return number of parameters
    size_t size() const { return m_parameters.size(); }

    void push_back(FitParameter *par) { m_parameters.push_back(par); }
    //! return begin of container
    iterator begin() { return m_parameters.begin(); }
    const_iterator begin() const { return m_parameters.begin(); }

    //! return end of container
    iterator end() { return m_parameters.end(); }
    const_iterator end() const { return m_parameters.end(); }

    //! access to parameters
    const FitParameter *operator[](size_t index) const { return m_parameters[check_index(index)]; }
    FitParameter *operator[](size_t index) { return m_parameters[check_index(index)]; }
    const FitParameter *operator[](std::string name) const { return getParameter(name); }
    FitParameter *operator[](std::string name) { return getParameter(name); }

    //! linking fit parameters with pool parameters
    void link_to_pool(const ParameterPool *pool);

    //! return number of free parameters
    size_t getNfreeParameters() const;

    //! return true if parameters have already given values
    bool valuesAreDifferrent(const double *pars_valuers, double tolerance_factor=1.0) const;

    void printParameters() const;

private:
    inline size_t check_index(size_t index) const { return (index < m_parameters.size() ? index : throw  OutOfBoundsException("FitSuiteParameters::check_index() -> Index out of bounds") ); }
    parameters_t m_parameters; //! collection of fit parameters
};

#endif // FITSUITEPARAMETERS_H
