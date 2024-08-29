/*!
 *  \file       test_basics.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <iostream>

#include "basics.hpp"

TEST(UTest4Basics, DefineUserClasses)
{
    class X
    {
    private:
        int m;
    public:
        explicit X(int i) : m{i}
        {
        }
    public:
        int mf(int i)
        {
            int old = m;
            m = i;
            return old;
        }
    };

    X var(5);

    auto user = [](X obj, X* ptr) {
        int x = obj.mf(7);
        int y = ptr->mf(9);
        // int z = obj.m;   // Error

        std::cout << "x = " << x << "\n"
                  << "y = " << y << std::endl;
    };

    user(var, &var);
}

TEST(UTest4Basics, CheckUserDefinedDate)
{
    /*!
     *  \note       对于无参数的默认构造函数，实例化时写成如下的()形式，会被编译器解释成一个函数声明.
     *  \warning    Empty parentheses interpreted as a function declaration.
     */
    // Date today();
    /*!
     *  \note       而写成{}形式，就没有此等warning，编译器据此判断为一个调用默认构造函数的实例化。
     */
    Date today{};
    EXPECT_EQ(today.get_year(), 2024);
    // EXPECT_EQ(today.get_month(), 7);

    Date xmas(25, 12, 2023);
    xmas.add_year(1);
    /*!
     *  \attention  由于构造函数定义了类的初始化方法，我们可以使用{}初始化方法。
     *              Bjarne Stroustrup建议优先使用{}而不是()，因为{}明确表明了要做什么（初始化），从而
     *              避免了某些潜在的错误，而且可以一致地使用。
     *              有些情况下必须使用()记法，但这种情况很少。
     */
    Date my_birthday{2, 1, 1983};
}

static void my_fnct(Date d)
{
    (void)d;
}

TEST(UTest4Basics, CheckExplicitInitialization)
{
    Date d1{15};            // OK: 被看作是显式类型转换
    Date d2 = Date{15};     // OK: 显示类型转换
    // Date d3 = {15};         // Error: = 方式的初始化不能进行隐式类型转换
    // Date d4 = 15;           // Error: = 方式的初始化不能进行隐式类型转换

    auto fn = []() {
        // my_fnct(15);        // Error: 参数传递不能进行隐式类型转换
        // my_fnct({15});      // Error: 参数传递不能进行隐式类型转换
        my_fnct(Date{15});      // OK: 显式类型转换
    };
    fn();
}

TEST(UTest4Basics, ExplicitCanAlsoBeUsedInMultipleArguments)
{
#include <iostream>

    struct X
    {
        /*!
         *  \attention  大多数explicit起重要作用的构造函数都接受单一参数。
         *              但是，explicit也可以用于无参或多个参数的构造函数。
         */
        explicit X()
        {
            std::cout << "called the explicit X(), no argument." << std::endl;
        }
        explicit X(int, int)
        {
            std::cout << "called the explicit X(int, int), with multiple arguments." << std::endl;
        }
    };

    // X x1 = {};      // Error: 隐式的转换
    // X x2 = {1, 2};  // Error: 隐式的转换

    X x3{};         // OK: 显式的构造函数
    X x4{1, 2};     // OK: 显式的构造函数

    auto fn = [](X arg) -> int {
        (void)arg;
        return int{};
    };

    // int i1 = fn({});        // Error: 隐式的参数
    // int i2 = fn({1, 2});    // Error: 隐式的
    int i3 = fn(X{});       // OK: 显式的
    int i4 = fn(X{1, 2});   // OK: 显式的
}

TEST(UTest4Basics, CheckConstAndMutableObjects)
{
    auto fn = [](Date date, const Date cdate) {
        // string_rep()方法既可以用于const对象，也可以用于非const对象。
        std::string s1 = date.string_rep();
        std::string s2 = cdate.string_rep();
    };

    Date today;
    const Date birthday{2, 1};

    fn(today, birthday);
}

TEST(UTest4Basics, CheckSelfReference)
{
    auto fn = [](Date& date) -> void {
        date.increase_day(1).increase_month(1).increase_year(1);
    };

    Date xmas(26, 12);
    fn(xmas);

    EXPECT_EQ(xmas.get_day(), 27);
    EXPECT_EQ(xmas.get_month(), 1);
}

struct X
{
    int fn();
    int m;

    static int sm;
};

int X::sm{7};

int X::fn()
{
    return m;
}

TEST(UTest4Basics, AccessClassMembers)
{
    auto user = [](X obj, X* ptr) {
        obj.m = 1;
        ptr->m = 2;
    };

    X a{5};
    X b{12};
    user(a, &b);

    EXPECT_EQ(a.fn(), 5);
    EXPECT_EQ(b.fn(), 2);

    std::printf("&X::fn address = %p\n", &X::fn);   // int (X::*)pfn(){&X::fn}
}

TEST(UTest4Basics, CheckClassStaticMemberAndFunction)
{
    Date copy_of_default_date = Date{};

    auto fn = [](Date date) {
        std::cout << "date.day = " << date.get_day() << std::endl;
        std::cout << "date.month = " << date.get_month() << std::endl;
        std::cout << "date.year = " << date.get_year() << std::endl;
    };

    auto gc = [&fn]() {
        fn(Date{});
    };

    gc();
}
