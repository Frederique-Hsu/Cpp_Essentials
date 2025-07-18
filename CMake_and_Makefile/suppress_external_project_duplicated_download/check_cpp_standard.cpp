/*!
 *  \file       check_cpp_standard.cpp
 *  \brief      Make sure that current program is using the correct C++ standard no. you have specified.
 *
 */

#include <gtest/gtest.h>

TEST(UTester4CppStandard, CheckCppStandardNo)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void *) * 8 << "-bits.\n"
              << std::endl;

    EXPECT_TRUE(__cplusplus == 201703L);
}