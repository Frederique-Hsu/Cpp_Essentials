/*!
 *  \file       macros.hpp
 *  \brief
 *
 */


#pragma once

#define SQUARE(a)   (a)*(a)
#define MIN(a, b)   (((a) < (b)) ? (a) : (b))

/*!
 *  \note   编写宏时，可以使用##宏运算符把两个字符串拼接成一个.
 *          如果参数的名字前有一个单独的#，表示是将该参数转化为字符串
 */
#define NAME2(a, b)     a##b
#define PRINTX(x)       std::cout << #x " = " << x << std::endl

#undef X    // 确保没有任何一个宏定义 X --- 不论是在之前，还是在之后.

/*!
 *  \remark     宏的参数列表可以为空，
 *              宏甚至可以是变参数的
 */
#define EMPTY()         std::cout << "empty" << std::endl
#define ERR_PRINT(...)  fprintf(stderr, "error: %s %d\n", __VA_ARGS__)

namespace macros
{
/*!
 *  \note   在现代C++语言中，auto, constexpr, const, decltype, enum, inline, lambda,
 *          namespace和template机制可以完成原来的宏与处理机制的大多数功能。如下：
 *
 *          min可完全替代MIN，而且更安全。
 */
template<class T>
inline const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}
}
