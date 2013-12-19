// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonCoreList.h"
#include "StochasticDoubleGaussian.pypp.h"

namespace bp = boost::python;

struct StochasticDoubleGaussian_wrapper : StochasticDoubleGaussian, bp::wrapper< StochasticDoubleGaussian > {

    StochasticDoubleGaussian_wrapper(double average, double std_dev )
    : StochasticDoubleGaussian( average, std_dev )
      , bp::wrapper< StochasticDoubleGaussian >(){
        // constructor
    
    }

    virtual ::StochasticDoubleGaussian * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->StochasticDoubleGaussian::clone(  );
    }
    
    
    ::StochasticDoubleGaussian * default_clone(  ) const  {
        return StochasticDoubleGaussian::clone( );
    }

    virtual double getFWHM(  ) const  {
        if( bp::override func_getFWHM = this->get_override( "getFWHM" ) )
            return func_getFWHM(  );
        else
            return this->StochasticDoubleGaussian::getFWHM(  );
    }
    
    
    double default_getFWHM(  ) const  {
        return StochasticDoubleGaussian::getFWHM( );
    }

    virtual double probabilityDensity( double value ) const  {
        if( bp::override func_probabilityDensity = this->get_override( "probabilityDensity" ) )
            return func_probabilityDensity( value );
        else
            return this->StochasticDoubleGaussian::probabilityDensity( value );
    }
    
    
    double default_probabilityDensity( double value ) const  {
        return StochasticDoubleGaussian::probabilityDensity( value );
    }

    virtual void setToRandom(  ) {
        if( bp::override func_setToRandom = this->get_override( "setToRandom" ) )
            func_setToRandom(  );
        else
            this->StochasticDoubleGaussian::setToRandom(  );
    }
    
    
    void default_setToRandom(  ) {
        StochasticDoubleGaussian::setToRandom( );
    }

    virtual double getRandom(  ) {
        if( bp::override func_getRandom = this->get_override( "getRandom" ) )
            return func_getRandom(  );
        else
            return this->StochasticParameter< double >::getRandom(  );
    }
    
    
    double default_getRandom(  ) {
        return StochasticParameter< double >::getRandom( );
    }

    virtual void setToAverage(  ) {
        if( bp::override func_setToAverage = this->get_override( "setToAverage" ) )
            func_setToAverage(  );
        else
            this->StochasticParameter< double >::setToAverage(  );
    }
    
    
    void default_setToAverage(  ) {
        StochasticParameter< double >::setToAverage( );
    }

};

void register_StochasticDoubleGaussian_class(){

    { //::StochasticDoubleGaussian
        typedef bp::class_< StochasticDoubleGaussian_wrapper, bp::bases< StochasticParameter< double > >, boost::noncopyable > StochasticDoubleGaussian_exposer_t;
        StochasticDoubleGaussian_exposer_t StochasticDoubleGaussian_exposer = StochasticDoubleGaussian_exposer_t( "StochasticDoubleGaussian", bp::init< double, double >(( bp::arg("average"), bp::arg("std_dev") )) );
        bp::scope StochasticDoubleGaussian_scope( StochasticDoubleGaussian_exposer );
        { //::StochasticDoubleGaussian::clone
        
            typedef ::StochasticDoubleGaussian * ( ::StochasticDoubleGaussian::*clone_function_type )(  ) const;
            typedef ::StochasticDoubleGaussian * ( StochasticDoubleGaussian_wrapper::*default_clone_function_type )(  ) const;
            
            StochasticDoubleGaussian_exposer.def( 
                "clone"
                , clone_function_type(&::StochasticDoubleGaussian::clone)
                , default_clone_function_type(&StochasticDoubleGaussian_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::StochasticDoubleGaussian::getFWHM
        
            typedef double ( ::StochasticDoubleGaussian::*getFWHM_function_type )(  ) const;
            typedef double ( StochasticDoubleGaussian_wrapper::*default_getFWHM_function_type )(  ) const;
            
            StochasticDoubleGaussian_exposer.def( 
                "getFWHM"
                , getFWHM_function_type(&::StochasticDoubleGaussian::getFWHM)
                , default_getFWHM_function_type(&StochasticDoubleGaussian_wrapper::default_getFWHM) );
        
        }
        { //::StochasticDoubleGaussian::getStdDev
        
            typedef double ( ::StochasticDoubleGaussian::*getStdDev_function_type )(  ) const;
            
            StochasticDoubleGaussian_exposer.def( 
                "getStdDev"
                , getStdDev_function_type( &::StochasticDoubleGaussian::getStdDev ) );
        
        }
        { //::StochasticDoubleGaussian::probabilityDensity
        
            typedef double ( ::StochasticDoubleGaussian::*probabilityDensity_function_type )( double ) const;
            typedef double ( StochasticDoubleGaussian_wrapper::*default_probabilityDensity_function_type )( double ) const;
            
            StochasticDoubleGaussian_exposer.def( 
                "probabilityDensity"
                , probabilityDensity_function_type(&::StochasticDoubleGaussian::probabilityDensity)
                , default_probabilityDensity_function_type(&StochasticDoubleGaussian_wrapper::default_probabilityDensity)
                , ( bp::arg("value") ) );
        
        }
        { //::StochasticDoubleGaussian::setToRandom
        
            typedef void ( ::StochasticDoubleGaussian::*setToRandom_function_type )(  ) ;
            typedef void ( StochasticDoubleGaussian_wrapper::*default_setToRandom_function_type )(  ) ;
            
            StochasticDoubleGaussian_exposer.def( 
                "setToRandom"
                , setToRandom_function_type(&::StochasticDoubleGaussian::setToRandom)
                , default_setToRandom_function_type(&StochasticDoubleGaussian_wrapper::default_setToRandom) );
        
        }
        { //::StochasticParameter< double >::getRandom
        
            typedef StochasticDoubleGaussian exported_class_t;
            typedef double ( exported_class_t::*getRandom_function_type )(  ) ;
            typedef double ( StochasticDoubleGaussian_wrapper::*default_getRandom_function_type )(  ) ;
            
            StochasticDoubleGaussian_exposer.def( 
                "getRandom"
                , getRandom_function_type(&::StochasticParameter< double >::getRandom)
                , default_getRandom_function_type(&StochasticDoubleGaussian_wrapper::default_getRandom) );
        
        }
        { //::StochasticParameter< double >::setToAverage
        
            typedef StochasticDoubleGaussian exported_class_t;
            typedef void ( exported_class_t::*setToAverage_function_type )(  ) ;
            typedef void ( StochasticDoubleGaussian_wrapper::*default_setToAverage_function_type )(  ) ;
            
            StochasticDoubleGaussian_exposer.def( 
                "setToAverage"
                , setToAverage_function_type(&::StochasticParameter< double >::setToAverage)
                , default_setToAverage_function_type(&StochasticDoubleGaussian_wrapper::default_setToAverage) );
        
        }
    }

}
