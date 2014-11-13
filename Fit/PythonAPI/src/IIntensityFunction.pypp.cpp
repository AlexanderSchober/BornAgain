// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence
//! @brief Automatically generated boost::python code for PythonFitAPI

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "PythonFitList.h"
#include "IIntensityFunction.pypp.h"

namespace bp = boost::python;

struct IIntensityFunction_wrapper : IIntensityFunction, bp::wrapper< IIntensityFunction > {

    IIntensityFunction_wrapper()
    : IIntensityFunction()
      , bp::wrapper< IIntensityFunction >(){
        // null constructor
        m_pyobj = 0;
    }

    virtual ::IIntensityFunction * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual double evaluate( double value ) const {
        bp::override func_evaluate = this->get_override( "evaluate" );
        return func_evaluate( value );
    }

    PyObject* m_pyobj;

};

void register_IIntensityFunction_class(){

    { //::IIntensityFunction
        typedef bp::class_< IIntensityFunction_wrapper, std::auto_ptr< IIntensityFunction_wrapper >, boost::noncopyable > IIntensityFunction_exposer_t;
        IIntensityFunction_exposer_t IIntensityFunction_exposer = IIntensityFunction_exposer_t( "IIntensityFunction" );
        bp::scope IIntensityFunction_scope( IIntensityFunction_exposer );
        { //::IIntensityFunction::clone
        
            typedef ::IIntensityFunction * ( ::IIntensityFunction::*clone_function_type)(  ) const;
            
            IIntensityFunction_exposer.def( 
                "clone"
                , bp::pure_virtual( clone_function_type(&::IIntensityFunction::clone) )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IIntensityFunction::evaluate
        
            typedef double ( ::IIntensityFunction::*evaluate_function_type)( double ) const;
            
            IIntensityFunction_exposer.def( 
                "evaluate"
                , bp::pure_virtual( evaluate_function_type(&::IIntensityFunction::evaluate) )
                , ( bp::arg("value") ) );
        
        }
    }

}
