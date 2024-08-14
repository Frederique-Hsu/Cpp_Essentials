/*!
 *  \file       main.cpp
 *  \brief
 *
 */



#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard number is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
