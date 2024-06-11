/*!
 *  \file       test_function_overload.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <cmath>

#include "function_overload.hpp"

TEST(UTest4FunctionOverload, Check_AutomaticParseTheOverload)
{
    print(1L);
    print(1.0);
    print("hello");
    print(1);
    print(short{1});

    auto fn = [](char c, int i, short s, float f) {
        print(c);           // 精确匹配： 调用print(char)
        print(i);           // 精确匹配： 调用print(int)
        print(s);           // 整型提升： 调用print(int)
        print(f);           // float转换为double的提升： 调用平print(double)

        print('a');         // 精确匹配： 调用print(char)
        print(49);          // 精确匹配： 调用print(int)
        print(0);           // 精确匹配： 调用print(int)
        print("a");         // 精确匹配： 调用print(const char*)
        print(nullptr);     // nullptr_t转换成const char*的提升： 调用print(const char*)
    };

    std::cout << "\n" << std::endl;
    fn('X', 23, 0x56BA, float{2.34});

    auto gn = [](int i, char c, const char* p, double d) {
        print_int(i);       // OK
        print_char(c);      // OK
        print_string(p);    // OK

        /*!
         *  \warning    由于没有重载，下面的四个调用，要么是错误，要么是执行了各种各样的类型转换，而且编译器还无法
         *              给出警告，这极易发生错误。
         *
         *              使用重载技术可以在一定程度上增加编译器发现并拒绝不适当参数的机会。
         */
        print_int(c);       // 调用了print_int(int(c))，把原本输出字符变成输出数字
        print_char(i);      // 调用了print_char(char(i))，将int转换为char, 明显窄化了。
        // print_string(i);    // 错误
        print_int(d);       // 调用了print_int(int(d))，将double转换成int，窄化了。
    };

    std::cout << "\n" << std::endl;
    gn(23, 'X', "hello", std::atan(1.0) * 4);

    auto sqrt_overload = [](double d, float f) {
        float fval = sqrt(d);
        std::cout << "fval = " << fval << std::endl;

        double dval = sqrt(d);
        std::cout << "dval = " << dval << std::endl;

        fval = sqrt(f);
        dval = sqrt(f);
    };

    std::cout << "\n" << std::endl;
    sqrt_overload(double{2.345}, float{-0.45809});
}

TEST(UTest4FunctionOverload, Check_FunctionOverloadScope)
{
    /*!
     *  \note   基类和派生类提供的作用域不同，因此默认情况下基类函数和派生类函数不会发生重载。
     */
    struct Base
    {
        void fn(int)
        {
            std::cout << "called Base::fn(int)" << std::endl;
        }
    };

    struct Derived : Base
    {
        void fn(int)
        {
            std::cout << "called Derived::fn(int)" << std::endl;
        }
    };

    auto g = [](Derived& obj) {
        obj.fn(1);
    };

    Derived der;
    g(der);
}

TEST(UTest4FunctionOverload, Check_MultipleArgumentsFunctionOverloadParsing)
{
    int i = my::pow(2, 2);
    EXPECT_EQ(i, int{});
    int d = my::pow(2.0, 2.0);
    EXPECT_DOUBLE_EQ(d, double{});

    {
        using namespace std;
        complex<int> zint{};

        complex<int> z1 = my::pow(2, zint);
        complex<int> z2 = my::pow(zint, 2);
        complex<int> z3 = my::pow(zint, zint);
        EXPECT_TRUE(z1 == z2 and z2 == z3 and zint == z1);
    }

    // double dvalue = my::pow(2.0, 2);     // 存在歧义，是调用pow(int, int)还是pow(double, double)?
    double dvalue = my::pow(double{2.0}, double{2});    // 正确，确定调用pow(double, double)
}

TEST(UTest4FunctionOverload, Check_ManualOverResolution)
{
    auto k = [](int i) -> void {
        manual_overload_resultion::f1(i);
        manual_overload_resultion::f2(static_cast<int*>(0));
    };

    k(5);
}
