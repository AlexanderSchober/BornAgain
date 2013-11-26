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
#include "IFormFactorDecorator.pypp.h"

namespace bp = boost::python;

struct IFormFactorDecorator_wrapper : IFormFactorDecorator, bp::wrapper< IFormFactorDecorator > {

    virtual ::IFormFactorDecorator * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual double getHeight(  ) const  {
        if( bp::override func_getHeight = this->get_override( "getHeight" ) )
            return func_getHeight(  );
        else{
            return this->IFormFactorDecorator::getHeight(  );
        }
    }
    
    double default_getHeight(  ) const  {
        return IFormFactorDecorator::getHeight( );
    }

    virtual double getRadius(  ) const  {
        if( bp::override func_getRadius = this->get_override( "getRadius" ) )
            return func_getRadius(  );
        else{
            return this->IFormFactorDecorator::getRadius(  );
        }
    }
    
    double default_getRadius(  ) const  {
        return IFormFactorDecorator::getRadius( );
    }

    virtual double getVolume(  ) const  {
        if( bp::override func_getVolume = this->get_override( "getVolume" ) )
            return func_getVolume(  );
        else{
            return this->IFormFactorDecorator::getVolume(  );
        }
    }
    
    double default_getVolume(  ) const  {
        return IFormFactorDecorator::getVolume( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ISample * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else{
            return this->ISample::cloneInvertB(  );
        }
    }
    
    ::ISample * default_cloneInvertB(  ) const  {
        return ISample::cloneInvertB( );
    }

    virtual void createDistributedFormFactors( ::std::vector< IFormFactor* > & form_factors, ::std::vector< double > & probabilities, ::size_t nbr_samples ) const  {
        if( bp::override func_createDistributedFormFactors = this->get_override( "createDistributedFormFactors" ) )
            func_createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
        else{
            this->IFormFactor::createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
        }
    }
    
    void default_createDistributedFormFactors( ::std::vector< IFormFactor* > & form_factors, ::std::vector< double > & probabilities, ::size_t nbr_samples ) const  {
        IFormFactor::createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::complex_t evaluate( ::cvector_t const & k_i, ::Bin1DCVector const & k_f_bin, ::Bin1D alpha_f_bin ) const {
        bp::override func_evaluate = this->get_override( "evaluate" );
        return func_evaluate( boost::ref(k_i), boost::ref(k_f_bin), alpha_f_bin );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ISample::getCompositeSample( );
    }

    virtual int getNumberOfStochasticParameters(  ) const  {
        if( bp::override func_getNumberOfStochasticParameters = this->get_override( "getNumberOfStochasticParameters" ) )
            return func_getNumberOfStochasticParameters(  );
        else{
            return this->IFormFactor::getNumberOfStochasticParameters(  );
        }
    }
    
    int default_getNumberOfStochasticParameters(  ) const  {
        return IFormFactor::getNumberOfStochasticParameters( );
    }

    virtual bool isDistributedFormFactor(  ) const  {
        if( bp::override func_isDistributedFormFactor = this->get_override( "isDistributedFormFactor" ) )
            return func_isDistributedFormFactor(  );
        else{
            return this->IFormFactor::isDistributedFormFactor(  );
        }
    }
    
    bool default_isDistributedFormFactor(  ) const  {
        return IFormFactor::isDistributedFormFactor( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else{
            this->ISample::printSampleTree(  );
        }
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
        if( dynamic_cast< IFormFactorDecorator_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual int setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        if( bp::override func_setMatchedParametersValue = this->get_override( "setMatchedParametersValue" ) )
            return func_setMatchedParametersValue( wildcards, value );
        else{
            return this->IParameterized::setMatchedParametersValue( wildcards, value );
        }
    }
    
    int default_setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        return IParameterized::setMatchedParametersValue( wildcards, value );
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_IFormFactorDecorator_class(){

    { //::IFormFactorDecorator
        typedef bp::class_< IFormFactorDecorator_wrapper, bp::bases< IFormFactor >, boost::noncopyable > IFormFactorDecorator_exposer_t;
        IFormFactorDecorator_exposer_t IFormFactorDecorator_exposer = IFormFactorDecorator_exposer_t( "IFormFactorDecorator", bp::no_init );
        bp::scope IFormFactorDecorator_scope( IFormFactorDecorator_exposer );
        { //::IFormFactorDecorator::clone
        
            typedef ::IFormFactorDecorator * ( ::IFormFactorDecorator::*clone_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "clone"
                , bp::pure_virtual( clone_function_type(&::IFormFactorDecorator::clone) )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IFormFactorDecorator::getHeight
        
            typedef double ( ::IFormFactorDecorator::*getHeight_function_type )(  ) const;
            typedef double ( IFormFactorDecorator_wrapper::*default_getHeight_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "getHeight"
                , getHeight_function_type(&::IFormFactorDecorator::getHeight)
                , default_getHeight_function_type(&IFormFactorDecorator_wrapper::default_getHeight) );
        
        }
        { //::IFormFactorDecorator::getRadius
        
            typedef double ( ::IFormFactorDecorator::*getRadius_function_type )(  ) const;
            typedef double ( IFormFactorDecorator_wrapper::*default_getRadius_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "getRadius"
                , getRadius_function_type(&::IFormFactorDecorator::getRadius)
                , default_getRadius_function_type(&IFormFactorDecorator_wrapper::default_getRadius) );
        
        }
        { //::IFormFactorDecorator::getVolume
        
            typedef double ( ::IFormFactorDecorator::*getVolume_function_type )(  ) const;
            typedef double ( IFormFactorDecorator_wrapper::*default_getVolume_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "getVolume"
                , getVolume_function_type(&::IFormFactorDecorator::getVolume)
                , default_getVolume_function_type(&IFormFactorDecorator_wrapper::default_getVolume) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( IFormFactorDecorator_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            IFormFactorDecorator_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&IFormFactorDecorator_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( IFormFactorDecorator_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            IFormFactorDecorator_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&IFormFactorDecorator_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::cloneInvertB
        
            typedef ::ISample * ( ::ISample::*cloneInvertB_function_type )(  ) const;
            typedef ::ISample * ( IFormFactorDecorator_wrapper::*default_cloneInvertB_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::ISample::cloneInvertB)
                , default_cloneInvertB_function_type(&IFormFactorDecorator_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IFormFactor::createDistributedFormFactors
        
            typedef void ( ::IFormFactor::*createDistributedFormFactors_function_type )( ::std::vector< IFormFactor* > &,::std::vector< double > &,::size_t ) const;
            typedef void ( IFormFactorDecorator_wrapper::*default_createDistributedFormFactors_function_type )( ::std::vector< IFormFactor* > &,::std::vector< double > &,::size_t ) const;
            
            IFormFactorDecorator_exposer.def( 
                "createDistributedFormFactors"
                , createDistributedFormFactors_function_type(&::IFormFactor::createDistributedFormFactors)
                , default_createDistributedFormFactors_function_type(&IFormFactorDecorator_wrapper::default_createDistributedFormFactors)
                , ( bp::arg("form_factors"), bp::arg("probabilities"), bp::arg("nbr_samples") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( IFormFactorDecorator_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&IFormFactorDecorator_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IFormFactor::evaluate
        
            typedef ::complex_t ( ::IFormFactor::*evaluate_function_type )( ::cvector_t const &,::Bin1DCVector const &,::Bin1D ) const;
            
            IFormFactorDecorator_exposer.def( 
                "evaluate"
                , bp::pure_virtual( evaluate_function_type(&::IFormFactor::evaluate) )
                , ( bp::arg("k_i"), bp::arg("k_f_bin"), bp::arg("alpha_f_bin") ) );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( IFormFactorDecorator_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&IFormFactorDecorator_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IFormFactor::getNumberOfStochasticParameters
        
            typedef int ( ::IFormFactor::*getNumberOfStochasticParameters_function_type )(  ) const;
            typedef int ( IFormFactorDecorator_wrapper::*default_getNumberOfStochasticParameters_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "getNumberOfStochasticParameters"
                , getNumberOfStochasticParameters_function_type(&::IFormFactor::getNumberOfStochasticParameters)
                , default_getNumberOfStochasticParameters_function_type(&IFormFactorDecorator_wrapper::default_getNumberOfStochasticParameters) );
        
        }
        { //::IFormFactor::isDistributedFormFactor
        
            typedef bool ( ::IFormFactor::*isDistributedFormFactor_function_type )(  ) const;
            typedef bool ( IFormFactorDecorator_wrapper::*default_isDistributedFormFactor_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "isDistributedFormFactor"
                , isDistributedFormFactor_function_type(&::IFormFactor::isDistributedFormFactor)
                , default_isDistributedFormFactor_function_type(&IFormFactorDecorator_wrapper::default_isDistributedFormFactor) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( IFormFactorDecorator_wrapper::*default_printParameters_function_type )(  ) const;
            
            IFormFactorDecorator_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&IFormFactorDecorator_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type )(  ) ;
            typedef void ( IFormFactorDecorator_wrapper::*default_printSampleTree_function_type )(  ) ;
            
            IFormFactorDecorator_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&IFormFactorDecorator_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            IFormFactorDecorator_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &IFormFactorDecorator_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setMatchedParametersValue
        
            typedef int ( ::IParameterized::*setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            typedef int ( IFormFactorDecorator_wrapper::*default_setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            
            IFormFactorDecorator_exposer.def( 
                "setMatchedParametersValue"
                , setMatchedParametersValue_function_type(&::IParameterized::setMatchedParametersValue)
                , default_setMatchedParametersValue_function_type(&IFormFactorDecorator_wrapper::default_setMatchedParametersValue)
                , ( bp::arg("wildcards"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( IFormFactorDecorator_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            IFormFactorDecorator_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&IFormFactorDecorator_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( IFormFactorDecorator_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            IFormFactorDecorator_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&IFormFactorDecorator_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
