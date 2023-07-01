/*!
 *  \file       test_list.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <vector>
#include <initializer_list>
#include <complex>

#include "list.hpp"

TEST(UTester4List, CheckListAsArgument)
{
    f({1, 2});      // 正确： 调用f(S{1, 2})

    // g({1, 2});      // 错误： 存在二义性
    g(S{1, 2});     // 正确： 调用g(S)
    g(SS{1, 2});    // 正确： 调用g(SS)
}

TEST(UTester4List, CheckInitializerList)
{
    std::vector<double> vec = {1, 2, 3,14};

#if 0
    const double temp[] = {double{1}, double{2}, 3.14};
    const std::initializer_list<double> init_list{temp, sizeof(temp)/sizeof(double)};
    std::vector<double> dvec(init_list);
#endif

    std::initializer_list<int> lst{1, 2, 3, 4};
    std::cout << *lst.begin() << std::endl;
    // *lst.begin() = 5;   // 错误： initializer_list::begin()返回的是const，不可修改。
    // std::cout << *lst.begin() << std::endl;
}

TEST(UTester4List, CheckQualifiedList)
{
    S v{.a = 7, .b = 8};      // 直接初始化一个变量
    v = S{.a = 7, .b = 8};    // 用限定列表进行赋值
    S* p = new S{.a = 7, .b = 8};     // 使用限定列表在自由存储上构建对象

    delete p;

    /*==================================================================*/

    const int i = 5;
    double area = square(double{i});
    std::complex<double> z = square(std::complex<double>{i});

    std::cout << "The area is " << area << std::endl;
    std::cout << "z = " << z << std::endl;
}

TEST(UTester4List, CheckUnqualifiedList)
{
    int v{7};   // 初始化器 （直接初始化）
    int v2 = {7};   // 初始化器（拷贝初始化）

    v = {8};    // 赋值运算的右侧运算对象
    // v += {88};  // 赋值运算的右侧运算对象
    // {v} = 9;    // 错误： 不能作为赋值运算的左侧运算对象
    // v = v + {10};   // 错误： 不能作为非赋值运算符的运算对象
    f({.a = 10, .b = 0});       // 函数实参
    // return {11};     // 列表可作为返回值
}

TEST(UTester4List, CheckInitializerListAsArgument)
{
    int v1 = high_value({1, 2, 3, 4, 5, 6, 7});
    std::cout << "v1 = " << v1 << std::endl;

    int v2 = high_value({-1, 2, v1, 4, -9, 20, v1});
    std::cout << "v2 = " << v2 << std::endl;
}

TEST(UTester4List, CheckHowToDeduceTypeFromInitializerList)
{
    // auto x0 = {};       // 错误： 无法推断initializer_list<>的元素类型，因为缺少元素
    auto x1 = {1};
    std::cout << typeid(x1).name() << std::endl;
    EXPECT_EQ(*x1.begin(), 1);

    auto x2 = {1, 2};
    std::cout << typeid(x2).name() << std::endl;
    EXPECT_EQ(x2.size(), 2);

    auto x3 = {1.0, 2.0, 3.45};
    std::cout << typeid(x3).name() << std::endl;
    EXPECT_EQ(x3.size(), 3);;

    // auto x4 = {1, 2, 3.0};      // 错误： 元素类型不相同，推断不出initializer_list<>的类型
}

template<typename T> void deduce_type(T)
{
    std::cout << "current sizeof(T) = " << sizeof(T) << std::endl;
}

template<typename T> void deduce_type(const std::vector<T>& arg)
{
    std::cout << "current sizeof(arg) = " << sizeof(decltype(arg)) << std::endl;
}

TEST(UTester4List, FailedToDeduceUnqualifiedListTypeFromTemplateArgument)
{
    // deduce_type({});        // 错误： 初始化器的类型未知
    // deduce_type({1});       // 错误： 未限定的列表与“普通的T”不匹配
    auto x2 = {1, 2};
    deduce_type(x2);

    auto x3 = {1.2, 3.4, 5.6, 7.8, 9.0};
    deduce_type(x3);
    // deduce_type({1.2, 3.4, 5.6, 7.8, 9.0});      // 错误

    auto str_list = {"Kona", "Sidney"};
    deduce_type(std::vector<decltype(str_list)>{str_list});
    // deduce_container_type({"Kona", "Sidney"});      // 错误： 无法推断T

    deduce_type(std::vector<int>{1, 2, 3});   // 正确，类型T已明确指出
    deduce_type(std::vector<std::string>{"Kona", "Sidney"});    // 正确
}
