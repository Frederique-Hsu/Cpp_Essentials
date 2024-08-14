/*!
 *  \file       main.cpp
 *  \brief      研究C++标准库的一些utilities功能
 *
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
