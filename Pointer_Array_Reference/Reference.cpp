/*!
 *  \file       Reference.cpp
 *  \brief
 *
 */


#include "Reference.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <utility>

void different_type_swap(std::string& s, std::vector<int>& v)
{
    s.shrink_to_fit();
    myspace::swap(s, std::string{s});
    v.clear();
    myspace::swap(v, std::vector<int>{});
    v = {};
}

TEST(UTester4Reference, CheckLValueReference)
{
    using namespace std;

    int var = 1;
    int& r{var};    // r和var对应同一个int
    int x = r;      // x的值变为1
    EXPECT_EQ(x, 1);

    r = 2;      // var的值变为2
    EXPECT_EQ(var, 2);

    /*!
     *  \warning    为了确保引用对应某个对象（即把它绑定到某个对象），必须初始化引用。
     */
    // int& r2;    // 错误： 引用必须初始化
    extern int& r3;     // 正确： r3在别处初始化了

    /*=============================================================*/

    int obj = 12345;
    int& robj{obj};
    ++robj;     // obj的值加1
    EXPECT_EQ(obj, 12346);
    int* pref = &robj;      // pref指向obj
    cout << "pref = " << pref << endl;

    EXPECT_EQ(pref, &obj);
    cout << "robj = " << robj << endl;

    /*!
     *  \note   引用本身的值一旦初始化就不能再改变了，它永远都指向一开始指定的对象。
     *          引用不是对象, 而指针是一种对象.
     */
}

TEST(UTester4Reference, CheckHowToInstantiateReference)
{
    /*!
     *  \warning    普通变量的引用和常量的引用必须区分开来。
     *              为变量引入一个临时变量充满风险，当我们未该变量赋值时，实际上是在为一个转瞬即逝的临时量赋值。
     *              常量的引用则不存在这一问题，函数的实参经常定义成常量的引用。
     */
    double temp = double{1.0};      // 首先使用给定的值创建一个临时变量
    const double& ctempref{temp};   // 然后用这个临时变量作为ctempref的初始值

    const double cdr{1};
    // double& dr = 1;     // 错误： 此处需要左值
}

void increment(int& num)
{
    ++num;
}

int next(int p)
{
    return p+1;
}

TEST(UTester4Reference, ReferenceAsFunctionArgument)
{
    int obj = 12;
    increment(obj);
    EXPECT_EQ(obj, 13);

    obj = next(obj);
    EXPECT_EQ(obj, 14);
}

TEST(UTester4Reference, CheckMap)
{
    using namespace std;

    myspace::Map<string, int> buf;
    for (string str; cin >> str;)
    {
        ++buf[str];
    }

    for (const auto& item : buf)
    {
        cout << item.first << ": " << item.second << endl;
    }
}

/* RValue reference ==============================================================================*/
std::string f()
{
    return std::string();
}

std::string f(std::string&& s)
{
    if (s.size())
        s[0] = std::toupper(s[0]);
    return s;
}

TEST(UTester4RValueRef, CheckHowReferToRValue)
{
    std::string var{"Cambridge"};

    /*!
     *  \remark     右值引用可以绑定到右值，但不能绑定到左值。
     *              从这一点上来说，右值引用与左值引用正好相反
     */

    std::string& r1{var};               // 左值引用，r1绑定到var(左值)上
    // std::string& r2{f()};               // 左值引用，错误： f()是右值
    // std::string& r3{"Princeton"};       // 左值引用，错误：不允许绑定到临时变量

    std::string&& rr1{f()};             // 右值引用，正确：rr1绑定到一个右值（临时变量）
    // std::string&& rr2{var};             // 右值引用，错误：var是左值
    std::string&& rr3{"Oxford"};        // rr3引用的是一个临时变量，它的内容是"Oxford"

    const std::string& cr1{"Harvard"};      // 正确： 创建一个临时变量，然后把它绑定到cr1
}
