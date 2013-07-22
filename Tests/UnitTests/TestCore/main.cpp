#include "gtest/gtest.h"

#include "AxisDoubleTest.h"
#include "BeamTest.h"
#include "ChiSquaredModuleTest.h"
#include "CVectorTest.h"
#include "DetectorTest.h"
#include "SimulationTest.h"
#include "InstrumentTest.h"
#include "IParameterizedTest.h"
#include "KVectorTest.h"
#include "MaskTest.h"
#include "OutputDataIteratorTest.h"
#include "OutputDataTest.h"
#include "ParameterPoolTest.h"
#include "RealParameterWrapperTest.h"
#include "ThreadInfoTest.h"

struct ErrorStreamRedirect {
    ErrorStreamRedirect( std::streambuf * new_buffer )
        : old( std::cerr.rdbuf( new_buffer ) )
    { }

    ~ErrorStreamRedirect( ) {
        std::cerr.rdbuf( old );
    }

private:
    std::streambuf * old;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // redirect std::cerr stream
    std::stringstream oss;
    ErrorStreamRedirect redirecter( oss.rdbuf() );
    (void)redirecter;

    // run all google tests
    return RUN_ALL_TESTS();
}

