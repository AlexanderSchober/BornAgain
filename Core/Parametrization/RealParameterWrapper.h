// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RealParameterWrapper.h
//! @brief     Declares class RealParameterWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REALPARAMETERWRAPPER_H
#define REALPARAMETERWRAPPER_H

#include "AttLimits.h"
#include <string>

class IParameterized;

//! Wrapper to real parameter for remote access to its value and callback abilities
//! @class RealParameterWrapper
//! @ingroup tools_internal

class BA_CORE_API_ RealParameterWrapper {
public:
    explicit RealParameterWrapper(
        IParameterized* parent, const std::string& name,
        double* par, const AttLimits& limits=AttLimits::limitless());
    RealParameterWrapper(const RealParameterWrapper& other);
    RealParameterWrapper& operator=(const RealParameterWrapper& other);

    //! Sets value of wrapped parameter and emit signal
    void setValue(double value);

    //! Returns value of wrapped parameter
    double getValue() const { checkNull(); return *m_data; }

    //! Returns true if wrapped parameter was not initialized with proper real value
    bool isNull() const { return m_data ? false : true; }

    //! throw exception if parameter was not initialized with proper value
    void checkNull() const;

    //! Prints the parameter's address to an output stream
    friend std::ostream& operator<<(std::ostream& ostr, const RealParameterWrapper& p) {
        ostr << p.m_data; return ostr; }

    AttLimits getAttLimits() const { return m_limits; }

    bool operator==(const RealParameterWrapper &other) const {
        return (m_limits == other.m_limits) && (m_data == other.m_data); }
    bool operator!=(const RealParameterWrapper &other) const { return !(*this == other); }

private:
    void swapContent(RealParameterWrapper& other);

    IParameterized* m_parent; //!< IParametrized object that "owns" this pool
    std::string m_name;
    volatile double* m_data;
    AttLimits m_limits;
    std::string fullName(); //!< For use in error messages
};

#endif // REALPARAMETERWRAPPER_H
