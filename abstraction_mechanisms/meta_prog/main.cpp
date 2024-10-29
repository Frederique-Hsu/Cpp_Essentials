/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#define BOOST_TEST_MODULE "Unit Test for Meta-Programming project"
// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>

#if false
    int main(int argc, char* argv[])
    {
        return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
    }
#endif


BOOST_AUTO_TEST_CASE(CheckCppStandardNo)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    BOOST_CHECK(true);
}
