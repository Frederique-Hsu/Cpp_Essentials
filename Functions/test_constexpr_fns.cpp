/*!
 *  \file       test_constexpr_fns.cpp
 *  \brief      Make the unit test for constexpr functions.
 *
 */


#include "constexpr_fns.hpp"

#include <gtest/gtest.h>

TEST(UTester4ConstexprFns, CheckConstexprReturnPointer)
{
    static const int x = 5;
    constexpr const int* p1 = addr(x);
    constexpr int xalias = *p1;
    EXPECT_EQ(xalias, x);

    static int y = 10;
    constexpr const int* p2 = addr(y);
    // constexpr int yalias = *p2;
    // constexpr const int* tp = addr(5);
}

TEST(UTester4ConstexprFns, CheckConstexprConditionValue)
{
    constexpr int val = check(15);
    EXPECT_EQ(val, 15);
}
