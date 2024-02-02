/*!
 *  \file       test_constexpr_functions.h++
 *  \brief      Validate how the \a constexpr function affect the behaviour of function invokation.
 *
 */


#pragma once

#include <gtest/gtest.h>

/*!
 *  \note   When \a constexpr is used in a function definition, it means
 *          "should be usable in a constant expression when given constant expression as arguments"
 *
 *          When used in an object definition, it means
 *          "evaluate the initializer at compile time"
 */
constexpr int factorial(int n);

class UTest4ConstexprFunction : public ::testing::Test
{
public:
    void fn(int n);
};
