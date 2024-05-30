/*!
 *  \file       test_lists.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include "Lists.hpp"

#include <vector>
#include <complex>

TEST(UTest4Lists, CheckListsInitializer)
{
    using namespace std;

    vector<double> v = {1, 2, 3.14};    // 接受一个初始化器(initializer_list)列表作为构造函数
#if false   // 其构造过程如下：
    const double temp[] = {double{1}, double{2}, 3.14};
    const initializer_list<double> tmp(temp, sizeof(temp)/sizeof(double));
    vector<double> vec(tmp);
#endif
}

TEST(UTest4Lists, CheckInitializerListUnderlyingDataCannotBeModified)
{
    using namespace std;

    initializer_list<int> lst{1, 2, 3, 4, 5};
    cout << "*lst.begin() = " << *lst.begin() << endl;
    // *lst.begin() = 2;   // Error: lst不可修改
    cout << "*(lst.end()-1) = " << *(lst.end()-1) << endl;
    cout << "*lst.end() = " << *lst.end() << endl;
}

TEST(UTest4Lists, CheckQualifiedLists)
{
    S v{7, 8};              // 直接初始化一个变量
    v = S{10, 12};          // 用限定列表进行赋值

    EXPECT_EQ(v.a, 10);
    EXPECT_EQ(v.b, 12);

    S* p = new S{20, 30};   // 使用限定列表在自由存储上构建对象
    // do something...
    delete p;

    auto fn = [](int i) {
        using namespace std;

        double d = square(double(i));
        cout << "d = " << d << endl;

        complex<double> z = square(complex<double>{i});
        cout << "z.real() = " << z.real() << endl;
        cout << "z.imag() = " << z.imag() << endl;
    };

    fn(5);
}

TEST(UTest4Lists, CheckUnqualifiedLists)
{
        double v{7};       // 初始化器（直接初始化）
        int v2 = {7};   // 初始化器（拷贝初始化）

    #if false
        Matrix m;
        int v3 = m[{2, 3}];     // 未限定列表作为下标
    #endif

        v = {8};        // 未限定列表可作为=右侧运算对象，编译器可根据v的类型，推断出{8}的类型
        // v += {88};      // 未限定列表但不可作为+=的右侧运算对象, 因为编译器无法推断出{88}的类型
        EXPECT_EQ(v, 8);

        // {v} = 9;        // 错误：未限定列表不能作为赋值运算符的左侧运算对象
        // v = 7 + {10};   // 错误：未限定列表不能作为非赋值运算符的运算对象

        auto fn = [](double d) -> double {
            return {d * d};     // 未限定列表可作为返回值
        };

        double value = fn({10.0});     // 未限定列表作为函数实参
        EXPECT_DOUBLE_EQ(value, 100);
}

TEST(UTest4Lists, CheckVariadicArgumentsList)
{
    int v1 = high_value({1, 2, 3, 9, -10, 24, -58, 102, 83});
    EXPECT_EQ(v1, 102);
    int v2 = high_value({-1, 2, v1, 19, -48, 357, v1});
    EXPECT_EQ(v2, 357);
}

template<typename T> void deduceType(T arg)
{
    std::cout << "typeof(arg) = " << typeid(arg).name() << std::endl;
}

template<class T> void deduceContainerElementType(const std::vector<T>& args)
{
    if (args.size() == 0)
    {
        std::cout << "The container is empty." << std::endl;
    }
    else
    {
        std::cout << "The element type of container is" << typeid(args[0]).name() << std::endl;
    }
}

TEST(UTest4Lists, CheckAutoDeduceListElementType)
{
    // auto x0 = {};           // 错误： 缺少元素类型
    auto x1 = {1};          // initializer_list<int>
    std::cout << "typeof(x1) = " << typeid(x1).name() << std::endl;

    auto x2 = {1, 2};       // initializer_list<int>
    auto x3 = {1, 2, 3};    // initializer_list<int>
    // auto x4 = {1, 2.0};     // 错误： 元素类型不相同

#if false
    /*!
     *  \warning    无法通过推断未限定列表的类型。使其作为普通模板的实参
     */
    deduceType({});         // Error: 初始化器的类型未知
    deduceType({1});        // Error: 未限定的列表与“普通的T”不匹配
    deduceType({1, 2, 3});  // Error:

    deduceContainerElementType({1, 2, 3});          // 当容器的元素类型是模板时，未限定的列表作为实参也无法推断出来。
    deduceContainerElementType({"Kona", "Sidney"});
#else
    deduceType(std::initializer_list<int>{1, 2, 4, -10, 8});     // OK: 但限定的列表可以作为参数正常传入模板。

    deduceContainerElementType(std::vector<int>{1, 2, 3});
    deduceContainerElementType(std::vector<std::string>{"Kona", "Sydney"});
#endif
}
