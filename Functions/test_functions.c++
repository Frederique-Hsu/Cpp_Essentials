/*!
 *  \file       test_functions.c++
 *  \brief      Make the unit test for functions.
 *
 */


#include <gtest/gtest.h>

#include "functions.hpp"

TEST(UTest4Functions, CheckSwapFunction)
{
    int a = -10, b = 5;
    swap(&a, &b);

    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, -10);
}
