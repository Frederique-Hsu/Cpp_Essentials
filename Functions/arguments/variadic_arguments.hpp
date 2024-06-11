/*!
 *  \file       variadic_arguments.hpp
 *  \brief      研究数量未定的参数
 *
 */


#pragma once

#include <cstdio>
#include <unistd.h>
#include <initializer_list>
#include <vector>
#include <string>

/*!
 *  \section    数量未定的参数
 *
 *  \details    对于某些函数来说，很难明确制定调用时期望的参数数量和类型，要实现这样的接口,有三种选择：
 *
 *  \list
 *      \li     使用可变模板
 *              它允许我们以类型安全的方式处理任意类型，任意数量的参数。只要写一个小的模板元程序来解释参数列表的正确
 *              含义并采取适当的操作即可。
 *
 *      \li     使用initializer_list<T>作为参数类型
 *              它允许我们以类型安全的方式处理某种类型的、任意数量的参数。在大多数上下文中，这种元素类型相同的参数
 *              列表是最常见和最重要的情形。
 *
 *      \li     用省略号 ... 结束参数列表，表示“可能有更多参数”。
 *              它允许我们通过使用<cstdarg>中的宏处理（几乎）任意类型的、任意数量的参数。但这种方案并非类型安全的，
 *              并且很难用于复杂的用户自定义类型。从早期的C语言开始，人们就使用这种机制了。
 *  \endlist
 */


namespace my
{
    int fprintf(FILE*, const char* ...);
    int execl(const char* ...);
}

void error(int severity ...);
void error(int severity, std::initializer_list<std::string> err);
void error(int severity, const std::vector<std::string>& err);

std::vector<std::string> arguments(int argc, char* argv[]);
