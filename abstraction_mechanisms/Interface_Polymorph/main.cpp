/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#define BOOST_TEST_MODULE "Unit testing for Interface_Polymorph project"
// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#if false
    int main(int argc, char* argv[])
    {
        std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
        
        return boost::unit_test::unit_test_main(&boost_init_unit_test, argc, argv);
    }
#endif

BOOST_AUTO_TEST_CASE(DummyUnitTest)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    
    BOOST_CHECK(true);
}