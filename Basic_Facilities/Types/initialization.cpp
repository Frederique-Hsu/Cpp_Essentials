/*!
 *  \file       initialization.cpp
 *  \brief      研究C++的对象初始化问题
 *
 */


#include <gtest/gtest.h>
#include <vector>
#include <complex>

TEST(UTester4ObjectInitialization, CheckListInitialization)
{
    double val1 = 7.9;
    int x2 = val1;

    int val2 = 1025;
    char c2 = val2;

#if 0
    int x3{val1};   /*!< \warning   Type 'double' cannot be narrowed to 'int' in
                     *              in initializer list.
                     */
    char c3{val2};  /*! \warning    Non-constant-expression cannot be narrowed from
                     *              type 'int' to 'char' in initializer list.
                     */
    char c4{24};
    char c5{264};   /*! \warning    Constant expression evaluates to 264 which cannot be
                     *              narrowed to type 'char'.
                     */
    int x4{2.0};    /*! \warning    Type 'double' cannot be narrowed to 'int' in initializer list */
#endif
    auto z1{99};
    auto z2 = 99;

    std::vector<int> v1{99};
    std::vector<int> v2(99);
    std::vector<double> v3(10, 3.3);

    EXPECT_EQ(v1[0], 99);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v2.size(), 99);
    EXPECT_EQ(v2[0], 0);
    EXPECT_EQ(v3.size(), 10);
    for (auto& elem : v3)
    {
        EXPECT_DOUBLE_EQ(elem, 3.3);
    }

    std::vector<std::string> strvec1{"hello!"};
    // std::vector<std::string> strvec2("hello!");     /* 错误： vector的任何构造函数都不接受字符串字面值常量作为参数的 */

    /*!
     *  \note   空初始化器列表{}指定使用默认值进行初始化
     */
    int x4{};       // x4被赋值为0
    double d4{};    // d4被赋值为0.0
    char* p{};      // p被赋值为nullptr
    std::vector<int> v4{};  // v4被赋值为一个空向量
    std::string s4{};       // s4被赋值为""
}

TEST(UTester4ObjectInitialization, CheckObjectInitializationIfNoInitializer)
{
    /*!
     *  \note   如果没有指定初始化器，则全局变量、名字空间变量、局部static变量、static成员将会执行
     *          相应数据类型的列表{}初始化
     */
    int a;      // 等同于 int a{}; 因此a的值变为0
    double d;   // 等同于 double d{}; 因此d的值变为0.0
    /*!
     *  \note   对于局部变量和自由存储上的对象（堆对象）来说，除非它们位于用户自定义类型的默认构造函数，
     *          否则不会执行默认初始化。
     */
    int x{};
    char buf[1024]{};       // 对于任意i, buf[i]的值变为0

    int* p{new int{10}};        // *p的变为10
    char* q{new char[1024]{}};  // 对于任意i, q[i]的值变为0

    EXPECT_EQ(*p, 10);
    for (int index = 0; index < 1024; ++index)
    {
        EXPECT_EQ(*(q+index), 0);
    }
    delete p;
    delete q;

    EXPECT_NO_THROW("No memory leakage.");
}

TEST(UTester4ObjectInitialization, CheckInitializerList)
{
    /*!
     *  \note   在声明语句中，一对空括号()通常表示“函数”。因此，如果想显式地表达“执行默认初始化”的
     *          意愿，则需要使用{}
     */
    std::complex<double> z1(1, 2);  // 函数风格的初始化器（用构造函数执行初始化）
    std::complex<double> f1();      // 函数声明

    std::complex<double> z2{1, 2};  // 用构造函数初始化成{1, 2}
    std::complex<double> f2{};      // 用构造函数初始化成默认值{0, 0}
    /*!
     *  \note   当我们使用{}符号进行初始化时，不会进行窄化转换。
     *          在使用了auto的语句中，{}列表的类型被推断为std::initializer_list<T>
     */
#if 0
    auto x1{1,2,3,4};       /*! \warning    Initializer for variable 'x1' with type 'auto' contains
                             *              multiple expressions.
                             *              direct-list-initialization of 'auto' requires exactly
                             *              only one element.
                             * \note        for deduction to 'std::initilizer_list', use copy-list-initialization.
                             *              i.e. add '=' before the '{'
                             */
#endif
    auto x2 = {1.0, 2.25, 3.5};     // x2被推断为std::iniitlizer_list<double>
    EXPECT_EQ(x2.size(), 3);
}
