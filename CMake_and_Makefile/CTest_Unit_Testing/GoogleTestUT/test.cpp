/*!
 *  \file       test.cpp
 *  \brief
 *
 */


#include "gtest/gtest.h"
#include "sum_integers.hpp"


TEST(UTest4SumUp, Sum_Zero)
{
    auto integers = {1, -1, 2, -2, 3, -3};
    auto result = sum_integers(integers);

    EXPECT_EQ(result, 0);
}

TEST(UTest4SumUp, Sum_Five_Numbers)
{
    std::vector<int> integers{1, 2, 3, 4, 5};
    auto result = sum_integers(integers);

    ASSERT_EQ(result, 15);
}