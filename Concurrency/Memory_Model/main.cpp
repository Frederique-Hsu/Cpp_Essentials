/*!
 *  \file       main.cpp
 *  \brief      This file implements the main() portal function for current project.
 *
 */


#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(UTest4CppStandard, CheckCppStandardNo)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits." << std::endl;
}