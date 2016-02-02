// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "PythonCoreList.h"
#include "FTDecayFunction2DVoigt.pypp.h"

namespace bp = boost::python;

struct FTDecayFunction2DVoigt_wrapper : FTDecayFunction2DVoigt, bp::wrapper< FTDecayFunction2DVoigt > {

    FTDecayFunction2DVoigt_wrapper(FTDecayFunction2DVoigt const & arg )
    : FTDecayFunction2DVoigt( arg )
      , bp::wrapper< FTDecayFunction2DVoigt >(){
        // copy constructor
        m_pyobj = 0;
    }

    FTDecayFunction2DVoigt_wrapper(double decay_length_x, double decay_length_y, double eta )
    : FTDecayFunction2DVoigt( decay_length_x, decay_length_y, eta )
      , bp::wrapper< FTDecayFunction2DVoigt >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::FTDecayFunction2DVoigt * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->FTDecayFunction2DVoigt::clone(  );
        }
    }
    
    ::FTDecayFunction2DVoigt * default_clone(  ) const  {
        return FTDecayFunction2DVoigt::clone( );
    }

    virtual double evaluate( double qx, double qy ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( qx, qy );
        else{
            return this->FTDecayFunction2DVoigt::evaluate( qx, qy );
        }
    }
    
    double default_evaluate( double qx, double qy ) const  {
        return FTDecayFunction2DVoigt::evaluate( qx, qy );
    }

    virtual double getEta(  ) const  {
        if( bp::override func_getEta = this->get_override( "getEta" ) )
            return func_getEta(  );
        else{
            return this->FTDecayFunction2DVoigt::getEta(  );
        }
    }
    
    double default_getEta(  ) const  {
        return FTDecayFunction2DVoigt::getEta( );
    }

    PyObject* m_pyobj;

};

void register_FTDecayFunction2DVoigt_class(){

    { //::FTDecayFunction2DVoigt
        typedef bp::class_< FTDecayFunction2DVoigt_wrapper, bp::bases< IFTDecayFunction2D >, std::auto_ptr< FTDecayFunction2DVoigt_wrapper > > FTDecayFunction2DVoigt_exposer_t;
        FTDecayFunction2DVoigt_exposer_t FTDecayFunction2DVoigt_exposer = FTDecayFunction2DVoigt_exposer_t( "FTDecayFunction2DVoigt", "2 dimensional Voigt decay function in reciprocal space.", bp::init< double, double, double >(( bp::arg("decay_length_x"), bp::arg("decay_length_y"), bp::arg("eta") )) );
        bp::scope FTDecayFunction2DVoigt_scope( FTDecayFunction2DVoigt_exposer );
        { //::FTDecayFunction2DVoigt::clone
        
            typedef ::FTDecayFunction2DVoigt * ( ::FTDecayFunction2DVoigt::*clone_function_type)(  ) const;
            typedef ::FTDecayFunction2DVoigt * ( FTDecayFunction2DVoigt_wrapper::*default_clone_function_type)(  ) const;
            
            FTDecayFunction2DVoigt_exposer.def( 
                "clone"
                , clone_function_type(&::FTDecayFunction2DVoigt::clone)
                , default_clone_function_type(&FTDecayFunction2DVoigt_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::FTDecayFunction2DVoigt::evaluate
        
            typedef double ( ::FTDecayFunction2DVoigt::*evaluate_function_type)( double,double ) const;
            typedef double ( FTDecayFunction2DVoigt_wrapper::*default_evaluate_function_type)( double,double ) const;
            
            FTDecayFunction2DVoigt_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::FTDecayFunction2DVoigt::evaluate)
                , default_evaluate_function_type(&FTDecayFunction2DVoigt_wrapper::default_evaluate)
                , ( bp::arg("qx"), bp::arg("qy") ) );
        
        }
        { //::FTDecayFunction2DVoigt::getEta
        
            typedef double ( ::FTDecayFunction2DVoigt::*getEta_function_type)(  ) const;
            typedef double ( FTDecayFunction2DVoigt_wrapper::*default_getEta_function_type)(  ) const;
            
            FTDecayFunction2DVoigt_exposer.def( 
                "getEta"
                , getEta_function_type(&::FTDecayFunction2DVoigt::getEta)
                , default_getEta_function_type(&FTDecayFunction2DVoigt_wrapper::default_getEta) );
        
        }
    }

}