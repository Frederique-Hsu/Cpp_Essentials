/*!
 *  \file       Reference.cpp
 *  \brief
 *
 */


#include "Reference.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(UTester4Reference, CheckLValueReference)
{
    using namespace std;

    int var = 1;
    int& r{var};    // r和var对应同一个int
    int x = r;      // x的值变为1
    EXPECT_EQ(x, 1);

    r = 2;      // var的值变为2
    EXPECT_EQ(var, 2);

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
    double temp = double{1.0};      // 首先使用给定的值创建一个临时变量
    const double& ctempref{temp};   // 然后用这个临时变量错位ctempref的初始值

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

    Map<string, int> buf;
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
