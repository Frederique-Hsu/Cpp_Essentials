/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#define BOOST_TEST_MODULE custom_main
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>


int main(int argc, char* argv[], char* envp[])
{
    return boost::unit_test::unit_test_main(init_unit_test, argc, argv);
}