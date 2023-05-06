/*!
 *  \file       integer.cpp
 *  \brief      研究C++的整数类型
 *
 */



#include <gtest/gtest.h>

#include <iostream>

TEST(UTester4IntegerType, ExpressIntegerLiteral)
{
    std::cout << 0xF0UL << ' ' << 0LU << '\n';
}
