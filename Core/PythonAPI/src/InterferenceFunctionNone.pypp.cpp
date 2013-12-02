// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "InterferenceFunctionNone.pypp.h"

namespace bp = boost::python;

struct InterferenceFunctionNone_wrapper : InterferenceFunctionNone, bp::wrapper< InterferenceFunctionNone > {

    InterferenceFunctionNone_wrapper( )
    : InterferenceFunctionNone( )
      , bp::wrapper< InterferenceFunctionNone >(){
        // null constructor
    
    }

    virtual ::InterferenceFunctionNone * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->InterferenceFunctionNone::clone(  );
    }
    
    
    ::InterferenceFunctionNone * default_clone(  ) const  {
        return InterferenceFunctionNone::clone( );
    }

    virtual double evaluate( ::cvector_t const & q ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( boost::ref(q) );
        else
            return this->InterferenceFunctionNone::evaluate( boost::ref(q) );
    }
    
    
    double default_evaluate( ::cvector_t const & q ) const  {
        return InterferenceFunctionNone::evaluate( boost::ref(q) );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else
            return this->IParameterized::areParametersChanged(  );
    }
    
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else
            this->IParameterized::clearParameterPool(  );
    }
    
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ISample * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else
            return this->ISample::cloneInvertB(  );
    }
    
    
    ::ISample * default_cloneInvertB(  ) const  {
        return ISample::cloneInvertB( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else
            return this->IParameterized::createParameterTree(  );
    }
    
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else
            return this->ISample::getCompositeSample(  );
    }
    
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ISample::getCompositeSample( );
    }

    virtual double getKappa(  ) const  {
        if( bp::override func_getKappa = this->get_override( "getKappa" ) )
            return func_getKappa(  );
        else
            return this->IInterferenceFunction::getKappa(  );
    }
    
    
    double default_getKappa(  ) const  {
        return IInterferenceFunction::getKappa( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else
            this->IParameterized::printParameters(  );
    }
    
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else
            this->ISample::printSampleTree(  );
    }
    
    
    void default_printSampleTree(  ) {
        ISample::printSampleTree( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< InterferenceFunctionNone_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual int setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        if( bp::override func_setMatchedParametersValue = this->get_override( "setMatchedParametersValue" ) )
            return func_setMatchedParametersValue( wildcards, value );
        else
            return this->IParameterized::setMatchedParametersValue( wildcards, value );
    }
    
    
    int default_setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        return IParameterized::setMatchedParametersValue( wildcards, value );
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else
            return this->IParameterized::setParameterValue( name, value );
    }
    
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else
            this->IParameterized::setParametersAreChanged(  );
    }
    
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_InterferenceFunctionNone_class(){

    { //::InterferenceFunctionNone
        typedef bp::class_< InterferenceFunctionNone_wrapper, bp::bases< IInterferenceFunction >, boost::noncopyable > InterferenceFunctionNone_exposer_t;
        InterferenceFunctionNone_exposer_t InterferenceFunctionNone_exposer = InterferenceFunctionNone_exposer_t( "InterferenceFunctionNone", bp::init< >() );
        bp::scope InterferenceFunctionNone_scope( InterferenceFunctionNone_exposer );
        { //::InterferenceFunctionNone::clone
        
            typedef ::InterferenceFunctionNone * ( ::InterferenceFunctionNone::*clone_function_type )(  ) const;
            typedef ::InterferenceFunctionNone * ( InterferenceFunctionNone_wrapper::*default_clone_function_type )(  ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "clone"
                , clone_function_type(&::InterferenceFunctionNone::clone)
                , default_clone_function_type(&InterferenceFunctionNone_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::InterferenceFunctionNone::evaluate
        
            typedef double ( ::InterferenceFunctionNone::*evaluate_function_type )( ::cvector_t const & ) const;
            typedef double ( InterferenceFunctionNone_wrapper::*default_evaluate_function_type )( ::cvector_t const & ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::InterferenceFunctionNone::evaluate)
                , default_evaluate_function_type(&InterferenceFunctionNone_wrapper::default_evaluate)
                , ( bp::arg("q") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( InterferenceFunctionNone_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            InterferenceFunctionNone_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&InterferenceFunctionNone_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( InterferenceFunctionNone_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            InterferenceFunctionNone_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&InterferenceFunctionNone_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::cloneInvertB
        
            typedef ::ISample * ( ::ISample::*cloneInvertB_function_type )(  ) const;
            typedef ::ISample * ( InterferenceFunctionNone_wrapper::*default_cloneInvertB_function_type )(  ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::ISample::cloneInvertB)
                , default_cloneInvertB_function_type(&InterferenceFunctionNone_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( InterferenceFunctionNone_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&InterferenceFunctionNone_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( InterferenceFunctionNone_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&InterferenceFunctionNone_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IInterferenceFunction::getKappa
        
            typedef double ( ::IInterferenceFunction::*getKappa_function_type )(  ) const;
            typedef double ( InterferenceFunctionNone_wrapper::*default_getKappa_function_type )(  ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "getKappa"
                , getKappa_function_type(&::IInterferenceFunction::getKappa)
                , default_getKappa_function_type(&InterferenceFunctionNone_wrapper::default_getKappa) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( InterferenceFunctionNone_wrapper::*default_printParameters_function_type )(  ) const;
            
            InterferenceFunctionNone_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&InterferenceFunctionNone_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type )(  ) ;
            typedef void ( InterferenceFunctionNone_wrapper::*default_printSampleTree_function_type )(  ) ;
            
            InterferenceFunctionNone_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&InterferenceFunctionNone_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            InterferenceFunctionNone_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &InterferenceFunctionNone_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setMatchedParametersValue
        
            typedef int ( ::IParameterized::*setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            typedef int ( InterferenceFunctionNone_wrapper::*default_setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            
            InterferenceFunctionNone_exposer.def( 
                "setMatchedParametersValue"
                , setMatchedParametersValue_function_type(&::IParameterized::setMatchedParametersValue)
                , default_setMatchedParametersValue_function_type(&InterferenceFunctionNone_wrapper::default_setMatchedParametersValue)
                , ( bp::arg("wildcards"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( InterferenceFunctionNone_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            InterferenceFunctionNone_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&InterferenceFunctionNone_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( InterferenceFunctionNone_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            InterferenceFunctionNone_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&InterferenceFunctionNone_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
