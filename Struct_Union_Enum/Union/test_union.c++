/*!
 *  \file       test_union.c++
 *  \brief
 *
 */



#include <gtest/gtest.h>

#include "union.hpp"

void check(ComplexU x)
{
    // ComplexU u;
    // ComplexU u2 = x;    // Error: Called to implicitly-deleted default constructor of 'ComplexU'.

    x.m1 = 1;   // 正确： 给int成员赋值
    std::string s = x.m3;       // 从string成员中读取内容
}

TEST(UTester4Union, CheckDefaultInitializerForUnion)
{
    MyUnion x1;     // 执行默认初始化，使得x1.p = ""
    MyUnion x2{7};  // 初始化x2.a = 7

    EXPECT_EQ(x2.a, 7);

    std::cout << x1.p << std::endl;
}
