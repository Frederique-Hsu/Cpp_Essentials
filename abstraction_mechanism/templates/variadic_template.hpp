/*!
 *  \file       variadic_template.hpp
 *  \brief      Study how to program the variadic template function or class.
 *  \author     Frederique Hsu
 *  \date       Sun.    02 April 2023
 *
 */


#pragma once

#include <iostream>

/* Declaration ===================================================================================*/
/* 可变参数模板的所有函数和类必须先声明，再定义，才可以被用户调用。 */
template<typename T> void print_head(T head);
template<typename T, typename... Tail> void print(T head, Tail... tail);
void print();       /* 哪怕这样的跟模板函数同名的空函数都必须先声明 */


/* Implementation ================================================================================*/
template<typename T>
void print_head(T head)
{
    std::cout << head << "\t";
}

template<typename T, typename... Tail>
void print(T head, Tail... tail)
{
    print_head(head);       /* 对head做某些操作 */
    print(tail...);         /* 再次处理tail */
}

void print() {}     /* 不执行任何操作 */
