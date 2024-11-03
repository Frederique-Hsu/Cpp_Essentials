/*!
 *  \file       test_iteration_recursion.cc
 *  \brief      
 *  
 */


#include "iteration_recursion.hpp"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(UTest4IterationRecursion)

    BOOST_AUTO_TEST_CASE(CheckFactorial)
    {
        int result = factorial<5>();
        BOOST_CHECK_EQUAL(result, 120);

        result = factorial(4);
        BOOST_CHECK_EQUAL(result, 24);

        int x6 = Fac<6>::value;
        BOOST_CHECK_EQUAL(x6, 720);
    }

BOOST_AUTO_TEST_SUITE_END()