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
#include "ThreadInfo.pypp.h"

namespace bp = boost::python;

void register_ThreadInfo_class(){

    { //::ThreadInfo
        typedef bp::class_< ThreadInfo > ThreadInfo_exposer_t;
        ThreadInfo_exposer_t ThreadInfo_exposer = ThreadInfo_exposer_t( "ThreadInfo", bp::init< >() );
        bp::scope ThreadInfo_scope( ThreadInfo_exposer );
        { //::ThreadInfo::getBeginIndex
        
            typedef int ( ::ThreadInfo::*getBeginIndex_function_type )( int ) ;
            
            ThreadInfo_exposer.def( 
                "getBeginIndex"
                , getBeginIndex_function_type( &::ThreadInfo::getBeginIndex )
                , ( bp::arg("total_size") ) );
        
        }
        { //::ThreadInfo::getEndIndex
        
            typedef int ( ::ThreadInfo::*getEndIndex_function_type )( int ) ;
            
            ThreadInfo_exposer.def( 
                "getEndIndex"
                , getEndIndex_function_type( &::ThreadInfo::getEndIndex )
                , ( bp::arg("total_size") ) );
        
        }
        ThreadInfo_exposer.def_readwrite( "current_batch", &ThreadInfo::current_batch );
        ThreadInfo_exposer.def_readwrite( "current_thread", &ThreadInfo::current_thread );
        ThreadInfo_exposer.def_readwrite( "n_batches", &ThreadInfo::n_batches );
        ThreadInfo_exposer.def_readwrite( "n_threads", &ThreadInfo::n_threads );
    }

}
