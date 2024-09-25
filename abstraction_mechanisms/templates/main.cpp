/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}