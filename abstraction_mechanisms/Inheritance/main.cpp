/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char* argv[], char* envp[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}