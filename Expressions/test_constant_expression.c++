/*!
 *  \file       test_constant_expression.c++
 *  \brief
 *
 */


#include "test_constant_expression.h++"
#include "utilities.hpp"
#include "constant_expression.hpp"

#include <iostream>
#include <cmath>

TEST(UTester4ConstExpr, CheckHowToEvaluateConstExprVariable)
{
    int x1 = 7;

    constexpr int x2 = 8;
    // constexpr int x3 = x1;      // 错误： 初始化器不是常量表达式
    constexpr int x4 = x2;      // 正确

    constexpr int s1 = is_sqrt(9);
    CHECK_EQUAL(s1, 3);

    constexpr int s2 = is_sqrt(1234);
    std::cout << "sqrt(1234) = " << s2 << std::endl;
    CHECK_FALSE_TEXT(s2 * s2 == 1234, "current computation is wrong!");
}

TEST(UTester4ConstExpr, CheckConstVariableEvaluation)
{
    const int x = 9;
    const std::string s = "asdf";
    const int square_root = std::sqrt(x);

    constexpr int xx = x;
    // constexpr std::string ss = s;       // 错误：s不是字面值常量类型
    // constexpr int yy = square_root;     // 错误：sqrt(x)不是一个constexpr函数
}

TEST(UTester4ConstExpr, CheckLiteralType)
{
    constexpr Point p1{10, 20, 30};
    constexpr Point p2{p1.up(20)};
    constexpr int dist = radial_distance(p1);
    std::cout << "The distance is " << dist << std::endl;
}

TEST(UTester4ConstExpr, CheckAddressConstantExpression)
{
    constexpr const char* p1 = "Hello";
    constexpr const char* p2 = p1;

    std::cout << "p1 address = " << std::hex << &p1 << std::endl;

    constexpr const char* p3 = p1 + 2;
    std::cout << "p3 = " << p3 << std::endl;
    constexpr char c = p1[1];
    CHECK_EQUAL(c, 'e');
}
