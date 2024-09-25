/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#define BOOST_TEST_MODULE "unit test for Hierarchies project."
// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#if false
    int main(int argc, char* argv[], char* envp[])
    {
        std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
        std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

        return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
    }
#endif

BOOST_AUTO_TEST_CASE(DummyUnitTest)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    
    int* array = new int[10];   // Just for valgrind to examine the memory leakage purpose.
    delete [] array;
    
    BOOST_CHECK(true);
}