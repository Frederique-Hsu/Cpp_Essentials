/*!
 *  \file       meta_functions.hpp
 *  \brief      
 *  
 */


#pragma once


/*!
 *  \details    C++14在C++11基础上，以强化编译期数值计算为目的，新增了 constexpr 常量式函数的功能。
 *
 *  \li         允许声明局部变量，但仍然不能用静态局部变量
 *  \li         允许使用过程控制语句 if, switch, for, while do, while, 但拒绝 go 语句
 *  \li         允许返回 void
 *  \li         同步改进常量式类成员函数功能
 * 
 *              C++14 的常量式函数能够更有效地进行元编程，可以进行编译期非递归的迭代计算。
 */
constexpr int factorial_sum(int n);

void print_factorial_sum();

void misc();
