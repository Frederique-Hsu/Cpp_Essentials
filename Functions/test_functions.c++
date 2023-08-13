/*!
 *  \file       test_functions.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include "functions.hpp"

TEST(UTester4Functions, CheckFactorial)
{
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(3), 6);
    EXPECT_EQ(factorial(5), 120);
}
