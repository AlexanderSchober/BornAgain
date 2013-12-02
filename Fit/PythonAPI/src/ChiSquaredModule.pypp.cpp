// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonFitList.h"
#include "ChiSquaredModule.pypp.h"

namespace bp = boost::python;

struct ChiSquaredModule_wrapper : ChiSquaredModule, bp::wrapper< ChiSquaredModule > {

    ChiSquaredModule_wrapper( )
    : ChiSquaredModule( )
      , bp::wrapper< ChiSquaredModule >(){
        // null constructor
    
    }

    ChiSquaredModule_wrapper(::ChiSquaredModule const & other )
    : ChiSquaredModule( boost::ref(other) )
      , bp::wrapper< ChiSquaredModule >(){
        // copy constructor
    
    }

    virtual double calculateChiSquared(  ) {
        if( bp::override func_calculateChiSquared = this->get_override( "calculateChiSquared" ) )
            return func_calculateChiSquared(  );
        else
            return this->ChiSquaredModule::calculateChiSquared(  );
    }
    
    
    double default_calculateChiSquared(  ) {
        return ChiSquaredModule::calculateChiSquared( );
    }

    virtual ::ChiSquaredModule * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->ChiSquaredModule::clone(  );
    }
    
    
    ::ChiSquaredModule * default_clone(  ) const  {
        return ChiSquaredModule::clone( );
    }

    virtual ::OutputData< double > * createChi2DifferenceMap(  ) const  {
        if( bp::override func_createChi2DifferenceMap = this->get_override( "createChi2DifferenceMap" ) )
            return func_createChi2DifferenceMap(  );
        else
            return this->ChiSquaredModule::createChi2DifferenceMap(  );
    }
    
    
    ::OutputData< double > * default_createChi2DifferenceMap(  ) const  {
        return ChiSquaredModule::createChi2DifferenceMap( );
    }

    virtual double getResidualValue( ::std::size_t index ) const  {
        if( bp::override func_getResidualValue = this->get_override( "getResidualValue" ) )
            return func_getResidualValue( index );
        else
            return this->ChiSquaredModule::getResidualValue( index );
    }
    
    
    double default_getResidualValue( ::std::size_t index ) const  {
        return ChiSquaredModule::getResidualValue( index );
    }

    virtual ::IFittingDataSelector const * getFittingDataSelector(  ) const  {
        if( bp::override func_getFittingDataSelector = this->get_override( "getFittingDataSelector" ) )
            return func_getFittingDataSelector(  );
        else
            return this->IChiSquaredModule::getFittingDataSelector(  );
    }
    
    
    ::IFittingDataSelector const * default_getFittingDataSelector(  ) const  {
        return IChiSquaredModule::getFittingDataSelector( );
    }

    virtual ::IIntensityFunction const * getIntensityFunction(  ) const  {
        if( bp::override func_getIntensityFunction = this->get_override( "getIntensityFunction" ) )
            return func_getIntensityFunction(  );
        else
            return this->IChiSquaredModule::getIntensityFunction(  );
    }
    
    
    ::IIntensityFunction const * default_getIntensityFunction(  ) const  {
        return IChiSquaredModule::getIntensityFunction( );
    }

    virtual ::IOutputDataNormalizer const * getOutputDataNormalizer(  ) const  {
        if( bp::override func_getOutputDataNormalizer = this->get_override( "getOutputDataNormalizer" ) )
            return func_getOutputDataNormalizer(  );
        else
            return this->IChiSquaredModule::getOutputDataNormalizer(  );
    }
    
    
    ::IOutputDataNormalizer const * default_getOutputDataNormalizer(  ) const  {
        return IChiSquaredModule::getOutputDataNormalizer( );
    }

    virtual ::IOutputDataNormalizer * getOutputDataNormalizer(  ) {
        if( bp::override func_getOutputDataNormalizer = this->get_override( "getOutputDataNormalizer" ) )
            return func_getOutputDataNormalizer(  );
        else
            return this->IChiSquaredModule::getOutputDataNormalizer(  );
    }
    
    
    ::IOutputDataNormalizer * default_getOutputDataNormalizer(  ) {
        return IChiSquaredModule::getOutputDataNormalizer( );
    }

    virtual void setFittingDataSelector( ::IFittingDataSelector const & selector ) {
        if( bp::override func_setFittingDataSelector = this->get_override( "setFittingDataSelector" ) )
            func_setFittingDataSelector( boost::ref(selector) );
        else
            this->IChiSquaredModule::setFittingDataSelector( boost::ref(selector) );
    }
    
    
    void default_setFittingDataSelector( ::IFittingDataSelector const & selector ) {
        IChiSquaredModule::setFittingDataSelector( boost::ref(selector) );
    }

    virtual void setIntensityFunction( ::IIntensityFunction const & intensity_function ) {
        if( bp::override func_setIntensityFunction = this->get_override( "setIntensityFunction" ) )
            func_setIntensityFunction( boost::ref(intensity_function) );
        else
            this->IChiSquaredModule::setIntensityFunction( boost::ref(intensity_function) );
    }
    
    
    void default_setIntensityFunction( ::IIntensityFunction const & intensity_function ) {
        IChiSquaredModule::setIntensityFunction( boost::ref(intensity_function) );
    }

    virtual void setOutputDataNormalizer( ::IOutputDataNormalizer const & data_normalizer ) {
        if( bp::override func_setOutputDataNormalizer = this->get_override( "setOutputDataNormalizer" ) )
            func_setOutputDataNormalizer( boost::ref(data_normalizer) );
        else
            this->IChiSquaredModule::setOutputDataNormalizer( boost::ref(data_normalizer) );
    }
    
    
    void default_setOutputDataNormalizer( ::IOutputDataNormalizer const & data_normalizer ) {
        IChiSquaredModule::setOutputDataNormalizer( boost::ref(data_normalizer) );
    }

};

void register_ChiSquaredModule_class(){

    { //::ChiSquaredModule
        typedef bp::class_< ChiSquaredModule_wrapper, bp::bases< IChiSquaredModule > > ChiSquaredModule_exposer_t;
        ChiSquaredModule_exposer_t ChiSquaredModule_exposer = ChiSquaredModule_exposer_t( "ChiSquaredModule", bp::init< >() );
        bp::scope ChiSquaredModule_scope( ChiSquaredModule_exposer );
        ChiSquaredModule_exposer.def( bp::init< ChiSquaredModule const & >(( bp::arg("other") )) );
        { //::ChiSquaredModule::calculateChiSquared
        
            typedef double ( ::ChiSquaredModule::*calculateChiSquared_function_type )(  ) ;
            typedef double ( ChiSquaredModule_wrapper::*default_calculateChiSquared_function_type )(  ) ;
            
            ChiSquaredModule_exposer.def( 
                "calculateChiSquared"
                , calculateChiSquared_function_type(&::ChiSquaredModule::calculateChiSquared)
                , default_calculateChiSquared_function_type(&ChiSquaredModule_wrapper::default_calculateChiSquared) );
        
        }
        { //::ChiSquaredModule::clone
        
            typedef ::ChiSquaredModule * ( ::ChiSquaredModule::*clone_function_type )(  ) const;
            typedef ::ChiSquaredModule * ( ChiSquaredModule_wrapper::*default_clone_function_type )(  ) const;
            
            ChiSquaredModule_exposer.def( 
                "clone"
                , clone_function_type(&::ChiSquaredModule::clone)
                , default_clone_function_type(&ChiSquaredModule_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ChiSquaredModule::createChi2DifferenceMap
        
            typedef ::OutputData< double > * ( ::ChiSquaredModule::*createChi2DifferenceMap_function_type )(  ) const;
            typedef ::OutputData< double > * ( ChiSquaredModule_wrapper::*default_createChi2DifferenceMap_function_type )(  ) const;
            
            ChiSquaredModule_exposer.def( 
                "createChi2DifferenceMap"
                , createChi2DifferenceMap_function_type(&::ChiSquaredModule::createChi2DifferenceMap)
                , default_createChi2DifferenceMap_function_type(&ChiSquaredModule_wrapper::default_createChi2DifferenceMap)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ChiSquaredModule::getResidualValue
        
            typedef double ( ::ChiSquaredModule::*getResidualValue_function_type )( ::std::size_t ) const;
            typedef double ( ChiSquaredModule_wrapper::*default_getResidualValue_function_type )( ::std::size_t ) const;
            
            ChiSquaredModule_exposer.def( 
                "getResidualValue"
                , getResidualValue_function_type(&::ChiSquaredModule::getResidualValue)
                , default_getResidualValue_function_type(&ChiSquaredModule_wrapper::default_getResidualValue)
                , ( bp::arg("index") ) );
        
        }
        { //::IChiSquaredModule::getFittingDataSelector
        
            typedef ::IFittingDataSelector const * ( ::IChiSquaredModule::*getFittingDataSelector_function_type )(  ) const;
            typedef ::IFittingDataSelector const * ( ChiSquaredModule_wrapper::*default_getFittingDataSelector_function_type )(  ) const;
            
            ChiSquaredModule_exposer.def( 
                "getFittingDataSelector"
                , getFittingDataSelector_function_type(&::IChiSquaredModule::getFittingDataSelector)
                , default_getFittingDataSelector_function_type(&ChiSquaredModule_wrapper::default_getFittingDataSelector)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IChiSquaredModule::getIntensityFunction
        
            typedef ::IIntensityFunction const * ( ::IChiSquaredModule::*getIntensityFunction_function_type )(  ) const;
            typedef ::IIntensityFunction const * ( ChiSquaredModule_wrapper::*default_getIntensityFunction_function_type )(  ) const;
            
            ChiSquaredModule_exposer.def( 
                "getIntensityFunction"
                , getIntensityFunction_function_type(&::IChiSquaredModule::getIntensityFunction)
                , default_getIntensityFunction_function_type(&ChiSquaredModule_wrapper::default_getIntensityFunction)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IChiSquaredModule::getOutputDataNormalizer
        
            typedef ::IOutputDataNormalizer const * ( ::IChiSquaredModule::*getOutputDataNormalizer_function_type )(  ) const;
            typedef ::IOutputDataNormalizer const * ( ChiSquaredModule_wrapper::*default_getOutputDataNormalizer_function_type )(  ) const;
            
            ChiSquaredModule_exposer.def( 
                "getOutputDataNormalizer"
                , getOutputDataNormalizer_function_type(&::IChiSquaredModule::getOutputDataNormalizer)
                , default_getOutputDataNormalizer_function_type(&ChiSquaredModule_wrapper::default_getOutputDataNormalizer)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IChiSquaredModule::getOutputDataNormalizer
        
            typedef ::IOutputDataNormalizer * ( ::IChiSquaredModule::*getOutputDataNormalizer_function_type )(  ) ;
            typedef ::IOutputDataNormalizer * ( ChiSquaredModule_wrapper::*default_getOutputDataNormalizer_function_type )(  ) ;
            
            ChiSquaredModule_exposer.def( 
                "getOutputDataNormalizer"
                , getOutputDataNormalizer_function_type(&::IChiSquaredModule::getOutputDataNormalizer)
                , default_getOutputDataNormalizer_function_type(&ChiSquaredModule_wrapper::default_getOutputDataNormalizer)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IChiSquaredModule::setFittingDataSelector
        
            typedef void ( ::IChiSquaredModule::*setFittingDataSelector_function_type )( ::IFittingDataSelector const & ) ;
            typedef void ( ChiSquaredModule_wrapper::*default_setFittingDataSelector_function_type )( ::IFittingDataSelector const & ) ;
            
            ChiSquaredModule_exposer.def( 
                "setFittingDataSelector"
                , setFittingDataSelector_function_type(&::IChiSquaredModule::setFittingDataSelector)
                , default_setFittingDataSelector_function_type(&ChiSquaredModule_wrapper::default_setFittingDataSelector)
                , ( bp::arg("selector") ) );
        
        }
        { //::IChiSquaredModule::setIntensityFunction
        
            typedef void ( ::IChiSquaredModule::*setIntensityFunction_function_type )( ::IIntensityFunction const & ) ;
            typedef void ( ChiSquaredModule_wrapper::*default_setIntensityFunction_function_type )( ::IIntensityFunction const & ) ;
            
            ChiSquaredModule_exposer.def( 
                "setIntensityFunction"
                , setIntensityFunction_function_type(&::IChiSquaredModule::setIntensityFunction)
                , default_setIntensityFunction_function_type(&ChiSquaredModule_wrapper::default_setIntensityFunction)
                , ( bp::arg("intensity_function") ) );
        
        }
        { //::IChiSquaredModule::setOutputDataNormalizer
        
            typedef void ( ::IChiSquaredModule::*setOutputDataNormalizer_function_type )( ::IOutputDataNormalizer const & ) ;
            typedef void ( ChiSquaredModule_wrapper::*default_setOutputDataNormalizer_function_type )( ::IOutputDataNormalizer const & ) ;
            
            ChiSquaredModule_exposer.def( 
                "setOutputDataNormalizer"
                , setOutputDataNormalizer_function_type(&::IChiSquaredModule::setOutputDataNormalizer)
                , default_setOutputDataNormalizer_function_type(&ChiSquaredModule_wrapper::default_setOutputDataNormalizer)
                , ( bp::arg("data_normalizer") ) );
        
        }
    }

}
