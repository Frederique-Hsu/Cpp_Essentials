/*!
 *  \file       test_variadic_template.cpp
 *  \brief      Make the unit test for user-defined variadic template function.
 *  
 */


#include "variadic_template.hpp"

#include <gtest/gtest.h>

TEST(UTester4VariadicTemplate, CheckHowVariadicTemplateFunctionWorks)
{
    std::cout << "First: ";
    print(1, 2.2, "hello");

    std::cout << "\nSecond: ";
    print(0.2, 'c', "yuck!", 3.1415926, 1024, 2023);
    std::cout << std::endl;
}