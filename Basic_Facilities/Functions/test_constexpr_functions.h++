/*!
 *  \file       test_constexpr_functions.h++
 *  \brief      Validate how the \a constexpr function affect the behaviour of function invokation.
 *
 */


#pragma once

#include <gtest/gtest.h>

class UTest4ConstexprAndReference : public ::testing::Test
{
protected:
    static constexpr int fib_list[] = {1, 1, 2, 3, 5, 8, 13, 21 /* , 34, 55, 89 */};
    static constexpr int fib(int n);
};
