/*!
 *  \file       scope.cpp
 *  \brief      研究C++的作用域问题
 *
 */


#include "scope.hpp"

#include <gtest/gtest.h>
#include <iostream>

namespace scope
{
    int x{0};       /* 全局变量 x */

    void fn()
    {
        int x;      /* 局部变量x隐藏了全局变量向x */
        x = 1;      /* 为局部变量向x赋值 */
        std::cout << "局部变量 x = " << x << std::endl;
        {
            int x;  /* 隐藏了上一个局部变量x */
            x = 2;  /* 为第二个局部变量x赋值 */
            std::cout << "第二个局部变量x的当前值为： " << x << std::endl;
        }
        x = 3;      /* 为第一个局部变量x赋值 */
        std::cout << "全局变量x的当前值为： " << x << std::endl;
    }

    int* p = &x;    /* 获取全局变量x的地址 */

    void accessHiddenGlobalVariable()
    {
        int x = -1;     /* 隐藏全局变量x */
        /*!
         *  \note       使用作用域解析运算符::访问被隐藏了的全局变量
         */
        ::scope::x = 128;   /* 为全局变量x赋值 */
        x = 2;              /* 为局部变量x赋值 */
        std::cout << "局部变量x = " << x << std::endl;
    }

    void assignLocalVarWithGlobalVar()  /*!< \warning   不合理： 在同一个作用域内使用了两个名字都是x的对象 */
    {
        int y = x;      /* 使用全局变量x，结果是y = 11 */
        std::cout << "把全局变量x赋给局部变量y = " << y << std::endl;

        int x = 22;
        y = x;      /* 使用局部变量x, 结果是y = 22 */
        std::cout << "把局部变量x赋给局部变量y = " << y << std::endl;
    }

    void useSameVariableInStatementScope(std::vector<std::string>& strings,
                                         std::list<int>& numbers)
    {
        using namespace std;

        /*!
         *  \note   在for语句中引入的名字是该语句的局部名字（位于语句作用域内）
         */
        for (const auto& x : strings)
        {
            cout << x << "\n";
        }
        for (auto x : numbers)
        {
            cout << x << "\n";
        }
        for (auto i = 0U; i != strings.size(); ++i)
        {
            cout << strings[i] << "\n";
        }
        for (auto i : {1, 2, 3, 4, 5, 6, 7})
        {
            cout << i << "\n";
        }
    }
}


TEST(UTester4Scope, CheckVariableScopeCover)
{
    using namespace std;

    cout << "全局变量 x = " << scope::x << endl;

    scope::fn();

    cout << "全局变量x的地址 = " << scope::p << endl;

    cout << "\n=========================================================================\n" << endl;

    scope::accessHiddenGlobalVariable();

    cout << "现在全局变量x变成了： " << scope::x << endl;
}

TEST(UTester4Scope, CheckAssignWithGlobalVariable)
{
    scope::x = 11;

    scope::assignLocalVarWithGlobalVar();
}
