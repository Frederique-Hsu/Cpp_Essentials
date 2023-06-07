/*!
 *  \file       test_enumerate.c++
 *  \brief
 *
 */



#include "enumerate.hpp"

#include <gtest/gtest.h>

TEST(UTester4Enumerate, AccessEnumerate)
{
    // Warning a1 = 7;     // 错误： 不存在int向Warning的类型转换
    // int a2 = green;         // 错误： green位于它的作用域之外
    // int a3 = Warning::green;    // 错误： 不存在Warnning向int的类型转换
    Warning a4 = Warning::green;    // 正确

    EXPECT_EQ(sizeof(Warning), sizeof(char));
    EXPECT_EQ(sizeof(a4), sizeof(char));

    EXPECT_EQ(static_cast<char>(Warning::green), 0);
    EXPECT_EQ(static_cast<char>(Warning::yellow), 1);
    EXPECT_EQ(static_cast<char>(Warning::orange), 2);
    EXPECT_EQ(static_cast<char>(Warning::red), 3);
}

TEST(UTester4Enumerate, ConvertIntToEnumerate)
{
    enum class Flag
    {
        x = 0x01,
        y = 0x02,
        z = 0x04,
        e = 0x08
    };

    EXPECT_EQ(sizeof(Flag), sizeof(char));   /* 如果没有显式地指定基础类型，则枚举类型的尺寸等于sizeof(int) */

    Flag f0{};          // f0的默认值是0
    // Flag f1 = 5;     // 类型错误： 5不属于Flag类型
    Flag f2 = Flag{5};  // 错误： 不允许窄化转换成enum class类型
    Flag f3 = static_cast<Flag>(5);     // “不近人情”的转换
    Flag f4 = static_cast<Flag>(999);   // 错误： 999不是一个char类型的值

    /* 每个枚举值对应一个整数，可以显式地把这个整数抽取出来 */
    int i = static_cast<int>(Flag::y);
    char c = static_cast<char>(Flag::e);
    EXPECT_EQ(i, 2);
    EXPECT_EQ(c, 8);
}
