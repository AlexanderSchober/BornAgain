#ifndef IDOUBLETOCOMPLEXFUNCTION_H_
#define IDOUBLETOCOMPLEXFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IDoubleToComplexFunction.h
//! @brief  Definition of HomogeneousMaterial class
//! @author herck
//! @date   27.04.2012

#include "Types.h"
#include "ICloneable.h"

//- -------------------------------------------------------------------
//! @class IDoubleToComplexFunction
//! @brief Base class for double to complex interpolators
//- -------------------------------------------------------------------
class IDoubleToComplexFunction : public ICloneable
{
public:
	virtual ~IDoubleToComplexFunction() {}
	virtual IDoubleToComplexFunction *clone() const=0;

	virtual complex_t evaluate(double value)=0;
};


//- -------------------------------------------------------------------
//! @class IDoubleToComplexMap
//! @brief Base class for double to complex map
//- -------------------------------------------------------------------
class IDoubleToComplexMap : public ICloneable
{
public:
    virtual ~IDoubleToComplexMap() {}
    virtual IDoubleToComplexMap *clone() const = 0;

    virtual const complex_t &evaluate(double value) const = 0;
};


//- -------------------------------------------------------------------
//! @class IDoubleToPairOfComplexMap
//! @brief Base class for double to complexpair_t map
//- -------------------------------------------------------------------
class IDoubleToPairOfComplexMap : public ICloneable
{
public:
    virtual ~IDoubleToPairOfComplexMap() {}
    virtual IDoubleToPairOfComplexMap *clone() const = 0;

    virtual const complexpair_t &evaluate(double value) const = 0;
};


class DoubleToComplexFunctionWrapper : public IDoubleToComplexFunction
{
public:
	typedef complex_t (*double_to_complex_t)(double);
	DoubleToComplexFunctionWrapper(double_to_complex_t function) : m_function(function) {}
	virtual DoubleToComplexFunctionWrapper *clone() const {
	    return new DoubleToComplexFunctionWrapper(m_function);
	}

	virtual complex_t evaluate(double value) { return m_function(value); }

private:
	double_to_complex_t m_function;
};

#endif /* IDOUBLETOCOMPLEXFUNCTION_H_ */
