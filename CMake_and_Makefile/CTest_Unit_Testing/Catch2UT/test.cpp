/*!
 *  \file       test.cpp
 *  \brief
 *
 */


#include "sum_integers.hpp"

#include <catch2/catch_test_macros.hpp>
#include <vector>

TEST_CASE("Sum of integers for a short vector", "[short]")
{
    std::vector<int> integers = {1, 2, 3, 4, 5};
    CHECK(sum_integers(integers) == 15);
}

TEST_CASE("Sum of integers for a longer vector", "[long]")
{
    std::vector<int> integers;
    for (int i = 1; i <= 1000; ++i)
    {
        integers.push_back(i);
    }

    CHECK(sum_integers(integers) == 500'500);
}