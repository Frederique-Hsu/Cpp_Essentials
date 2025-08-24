/*!
 *  \file       Test_Factorial.cc
 *  \brief      
 *  
 */


#include <catch2/catch_test_macros.hpp>

#include "Factorial.hpp"

TEST_CASE("Unit test for template recursive instantiation", "[check-recursive-factorial]")
{
    SECTION("Make an unit testing on recursive factorial")
    {
        int result_5 = Factorial<5>::value;

        CHECK(result_5 == 5 * 4 * 3 * 2 * 1);
    }

    SECTION("Check the tail recursion on factorial calculation")
    {
        auto result_10 = factorial_iter(10, 1);
        CHECK(result_10 == 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1);
    }
}