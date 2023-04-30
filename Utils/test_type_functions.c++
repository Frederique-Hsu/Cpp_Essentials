/*!
 *  \file       test_type_functions.c++
 *
 */


#include <gtest/gtest.h>

#include <limits>
#include <iostream>


TEST(UTester4TypeFunctions, CheckNumericLimitsValue)
{
    constexpr float minimal = std::numeric_limits<float>::min();

    std::cout << "The minimal float value is: " << minimal << std::endl;

    constexpr int size = sizeof(int);
    std::cout << "sizeof(int) = " << size << " bytes." << std::endl;
}
