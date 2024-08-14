/*!
 *  \file       constexpr_functions.cpp
 *  \brief
 *
 */


#include "constexpr_functions.hpp"


/*!
 *  \remark     constexpr函数必须足够简单才能在编译时求值。
 *
 *              constexpr函数必须包含一条独立的return语句，没有循环，也没有局部变量。
 *
 *              constexpr函数应该是一个纯函数，不能有副作用
 */

#if false
    int glob;

    constexpr void bad1(int a)      // 错误： constexpr函数不能是void
    {
        glob = a;       // 错误： 在constexpr函数中使用全局变量会有副作用
    }

    constexpr int bad2(int a)
    {
        if (a >= 0)     // 错误： 在constexpr函数中有if语句
            return a;
        else
            return -a;
    }

    constexpr int bad3(int a)
    {
        int sum = 0;        // 错误： 在constexpr函数中有局部变量
        for (int i = 0; i < a; ++i)     // 错误： 在constexpr函数中有循环
        {
            sum += factorial(i);
        }
        return sum;
    }
#endif
