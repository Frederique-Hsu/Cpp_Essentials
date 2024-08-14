/*!
 *  \file       list_arguments.hpp
 *  \brief      研究列表参数
 *
 */


#pragma once

#include <initializer_list>
#include <string>
#include <iostream>

/*!
 *  \section    列表参数
 *
 *              一个由{}限定的列表可以作为下列形参的实参
 *  \list
 *      \li     类型 \code std::initializer_list<T>, 其中列表的值能隐式地转换成T
 *      \li     能用列表中的值初始化的类型
 *      \li     T类型数组的引用，其中列表的值能隐式地转换成T
 *  \endlist
 */

#define LIST_ARGUMENTS_NOT_OVERLOADED       1
#define LIST_ARGUMENTS_OVERLOADED           2
#define LIST_ARGUMENTS                      LIST_ARGUMENTS_OVERLOADED

struct S
{
    int a;
    std::string s;
};

#if (LIST_ARGUMENTS == LIST_ARGUMENTS_NOT_OVERLOADED)
    template<class T> void f1(std::initializer_list<T>)
    {
        std::cout << "called f1<T>(std::initializer_list<T>)" << std::endl;
    }

    void f2(S);

    template<class T, int N> void f3(T (&r)[N])
    {
        (void)r;
        std::cout << "called f3<T, N>(T (&r)[N])" << std::endl;
    }

    void f4(int);
#elif (LIST_ARGUMENTS == LIST_ARGUMENTS_OVERLOADED)
    template<class T> void fn(std::initializer_list<T>)
    {
        std::cout << "called fn<T>(std::initializer_list<T>)" << std::endl;
    }

    void fn(S);

    template<class T, int N> void fn(T (&r)[N])
    {
        (void)r;
        std::cout << "called fn<T, N>(T (&r)[N])" << std::endl;
    }

    void fn(int);
#endif
