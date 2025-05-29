/*!
 *  \file       test_TMP.cc
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "../TMP_CRTP/template_meta_programming.hpp"

TEST(UTest4TMP, CheckFactorial)
{
    static_assert(factorial<4>::value == 24, "Failed to calculate the 4 factorial.");

    static_assert(fact(4) == 24, "Use the C++11 compile-time computation.");
}