/*!
 *  \file       test_arguments.c++
 *  \brief
 *
 */


#include "test_arguments.h++"

#include "function_arguments.hpp"
#include "array_arguments.hpp"
#include "list_arguments.hpp"
#include "variadic_arguments.hpp"
#include "default_arguments.hpp"

#include <cstring>


TEST(UTest4Arguments, Check_PointerPassedAsValue)
{
    auto fn = [](int* p, int* q) -> void {
        int* pp = find(p, q, 13);

        std::cout << "current p address = " << std::ios_base::hex << p << std::endl;
        std::cout << "current q address = " << q << std::endl;
        std::cout << "pp address = " << pp << std::endl;
    };

    int* numbers{nullptr};

    auto prepareData = [&numbers](std::size_t n) -> bool {
        // numbers = static_cast<decltype(numbers)>(alloca(sizeof(decltype(*numbers)) * n));
        numbers = static_cast<decltype(numbers)>(malloc(sizeof(decltype(*numbers)) * n));
        if (numbers == nullptr)
        {
            return false;
        }

        for (std::size_t index = 0; index < n; ++index)
        {
            *(numbers + index) = 5 * index + 3;
        }
        return true;
    };

    constexpr const int n = 30;
    EXPECT_EQ(prepareData(n), true);
    for (auto i = 0; i < n; ++i)
    {
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }

    std::cout << std::ios_base::hex << std::endl;
    std::cout << "numbers[0] address = " << numbers << std::endl;
    std::cout << "numbers[" << n - 1 << "] address = " << numbers + n - 1 << std::endl;

    fn(numbers, numbers + n - 1);

    auto destroyData = [&numbers]() {
        if (numbers != NULL)
        {
            free(numbers);
        }
    };
    destroyData();
}

TEST(UTest4Arguments, Check_RefArguments)
{
    auto f = [](int val, int& ref) {
        ++val;
        ++ref;
    };

    int i = 1;
    int j = 1;
    f(i, j);
    EXPECT_EQ(i, 1);
    EXPECT_EQ(j, 2);
}

TEST(UTest4Arguments, Check_ConstRefArguments)
{
    /*!
     *  \section    const ref
     *
     *  \details    与引用初始化规则相同，字面量，常量和需要执行类型转换的参数可以传给const T&参数，但是不能传给
     *              普通的T&参数。
     *
     *              一方面，我们允许向const T&的转换以确保凡是能传给T类型参数的值都能传给const T&类型的参数，
     *              实现方式是把值存入临时变量。
     *
     *              另一方面，禁止向非const引用参数转换，可以有效地规避临时变量带来的程序错误风险。
     */

    auto g1 = [](double d) -> void {
        float r = fsqrt(2.0f);      // 传递存放2.0f的临时变量的引用
        r = fsqrt(r);               // 传递r的引用
        r = fsqrt(d);               // 传递存放static_cast<float>(d)的临时变量的引用
    };

    g1(double{5.0});

    auto g2 = [](double d, float r) -> void {
        // update(2.0f);       // 错误：常量实参不能向非const T&类型转换
        update(r);
        // update(d);          // 错误： 需要执行类型转换
    };

    g2(double{5.0}, float{3.0});

    auto g3 = [](std::vector<int>& vi, const std::vector<int>& cvi) {
        fnref(vi);                          // 调用 fnref(vector<int>&)
        fnref(cvi);                         // 调用 fnref(const vector<int>&)
        fnref(std::vector<int>{1, 2, 3});   // 调用 fnref(vector<int>&&)
    };

    std::vector<int> odds{-3, -7, -9};
    const std::vector<int> evens{6, 8, 10, 20};
    g3(odds, evens);
}

TEST(UTest4Arguments, Check_ArrayArguments)
{
    char v[] = "Annemarie";
    int i = std::strlen(v);
    int j = std::strlen("Nicholas");

    int a1[] = {1, 2, 3, 4};
    int a2[] = {1, 2};

    compute(a1);    // OK
    // compute(a2);    // Error: 数组月a2的元素个数有误，不是4个。
}

TEST(UTest4Arguments, Check_ArrayArgumentsWithFixedSize)
{
    int a1[] = {1, 1, 2, 3, 5, 8, 13, 21} ;
    double a2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

    compute(a1);    // T是int, N自动推断出来为8个
    compute(a2);    // T是double, N自动推断出来为10个

    const char* week[] = {"Monday", "Tue", "Wed", "Thu", "Fri", "Sat", "Sunday"};
    auto num = sizeof(week)/sizeof(week[0]);
    EXPECT_EQ(num, 7);
}

TEST(UTest4Arguments, Check_ListArguments)
{
#if (LIST_ARGUMENTS == LIST_ARGUMENTS_NOT_OVERLOADED)
    f1({1, 2, 3, 4, 5});
    f2({1, "MKS"});

    int array[] = {1, 2, 3, 4};
    f3(array);
    f4({1});
#elif (LIST_ARGUMENTS == LIST_ARGUMENTS_OVERLOADED)
    fn({1, 2, 3, 4, 5});
    fn({1, "MKS"});

    int array[] = {1, 2, 3, 4};
    fn(array);
    fn({1});
    fn(int{1});
#endif
}

TEST(UTest4Arguments, Check_VariadicArguments)
{
    std::printf("Hello, world!\n");

    struct Name
    {
        std::string given_name;
        std::string family_name;
    };
    Name my{ .given_name = "Frederique", .family_name = "Hsu" };    /*! \warning    ISO C++ requires field designators t0 be specified in declaration order */
    std::printf("My name is %s %s.\n", my.given_name.c_str(), my.family_name.c_str());
}

TEST(UTest4Arguments, Check_DefaultArguments)
{
    auto test = [](X& a) {
        a.fn();
        a.def_arg = 9;
        a.fn();
    };

    X xobj;
    test(xobj);
}
