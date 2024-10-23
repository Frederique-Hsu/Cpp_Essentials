/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[], char* envp[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(UTest4CppStandard, CheckCppStandardNoAndProgram)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits." << std::endl;
}