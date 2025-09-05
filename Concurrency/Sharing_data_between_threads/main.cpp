/*!
 *  \file       main.cpp
 *  \brief      Define the common main() portal function for all sub-projects under the Sharing_data_between_threads/ directory.
 *  
 */


#define BOOST_TEST_MODULE "Boost Unit Test Module" 
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>

#if defined (BOOST_TEST_DYN_LINK) && defined (BOOST_TEST_NO_MAIN)
    int main(int argc, char* argv[])
    {
        return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
    }
#endif


BOOST_AUTO_TEST_SUITE(UTester4CppStandard)
    BOOST_AUTO_TEST_CASE(CheckCppStandardNo)
    {
        std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
        std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

        BOOST_CHECK_EQUAL(__cplusplus, 201703L);
    }
BOOST_AUTO_TEST_SUITE_END()