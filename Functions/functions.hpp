/*!
 *  \file       functions.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

void fn(int x);         /* 允许修改x */
void fn(const int x);   /* 不允许修改x */

/*!
 *  \note   函数返回类型可以放在函数名之前，也可以放在函数之后。
 *          以下2个函数声明是完全等价的。
 */
std::string to_string(int a);
auto to_string(int a) -> std::string;


int factorial(int n);
/*!
 *  \note   当constexpr(翻译为常量表达式)出现在函数定义中时，它的含义是：如果给定了常量表达式作为实参，则该函数应该
 *          能用在常量表达式中。
 *          而当constexpr出现在对象定义中时，它的含义是：在编译时对初始化器求值。
 */
constexpr int fac(int n)
{
    return (n > 1) ? n * fac(n-1) : 1;
}

int* fp();
int& fr();
