/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#define BOOST_TEST_MODULE "Unit testing for Interface_Polymorph project"
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    
    return boost::unit_test::unit_test_main(init_unit_test, argc, argv);
}

BOOST_AUTO_TEST_CASE(DummyUnitTest)
{
    BOOST_CHECK(true);
}