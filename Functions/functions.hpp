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
