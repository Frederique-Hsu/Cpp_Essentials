/*!
 *  \file   main.cpp
 *  \brief  This file implements the main() portal function for current project.
 *  \author Frederique Hsu
 *  \date   Thur.   12 Jan. 2023
 *  \copyright  2023    All rights reserved.
 *
 */


#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is: " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
