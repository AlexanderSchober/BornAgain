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
#include "IMaterial.pypp.h"

namespace bp = boost::python;

struct IMaterial_wrapper : IMaterial, bp::wrapper< IMaterial > {

    IMaterial_wrapper(IMaterial const & arg )
    : IMaterial( arg )
      , bp::wrapper< IMaterial >(){
        // copy constructor
        
    }

    IMaterial_wrapper(::std::string const & name )
    : IMaterial( name )
      , bp::wrapper< IMaterial >(){
        // constructor
    
    }

    virtual ::complex_t getRefractiveIndex(  ) const  {
        if( bp::override func_getRefractiveIndex = this->get_override( "getRefractiveIndex" ) )
            return func_getRefractiveIndex(  );
        else{
            return this->IMaterial::getRefractiveIndex(  );
        }
    }
    
    ::complex_t default_getRefractiveIndex(  ) const  {
        return IMaterial::getRefractiveIndex( );
    }

    virtual bool isScalarMaterial(  ) const  {
        if( bp::override func_isScalarMaterial = this->get_override( "isScalarMaterial" ) )
            return func_isScalarMaterial(  );
        else{
            return this->IMaterial::isScalarMaterial(  );
        }
    }
    
    bool default_isScalarMaterial(  ) const  {
        return IMaterial::isScalarMaterial( );
    }

};

void register_IMaterial_class(){

    { //::IMaterial
        typedef bp::class_< IMaterial_wrapper > IMaterial_exposer_t;
        IMaterial_exposer_t IMaterial_exposer = IMaterial_exposer_t( "IMaterial", bp::init< std::string const & >(( bp::arg("name") )) );
        bp::scope IMaterial_scope( IMaterial_exposer );
        { //::IMaterial::getRefractiveIndex
        
            typedef ::complex_t ( ::IMaterial::*getRefractiveIndex_function_type )(  ) const;
            typedef ::complex_t ( IMaterial_wrapper::*default_getRefractiveIndex_function_type )(  ) const;
            
            IMaterial_exposer.def( 
                "getRefractiveIndex"
                , getRefractiveIndex_function_type(&::IMaterial::getRefractiveIndex)
                , default_getRefractiveIndex_function_type(&IMaterial_wrapper::default_getRefractiveIndex) );
        
        }
        { //::IMaterial::isScalarMaterial
        
            typedef bool ( ::IMaterial::*isScalarMaterial_function_type )(  ) const;
            typedef bool ( IMaterial_wrapper::*default_isScalarMaterial_function_type )(  ) const;
            
            IMaterial_exposer.def( 
                "isScalarMaterial"
                , isScalarMaterial_function_type(&::IMaterial::isScalarMaterial)
                , default_isScalarMaterial_function_type(&IMaterial_wrapper::default_isScalarMaterial) );
        
        }
    }

}
