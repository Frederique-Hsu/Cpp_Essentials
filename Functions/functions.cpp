/*!
 *  \file       functions.cpp
 *  \brief
 *
 */


#include "functions.hpp"

void fn(int x)
{
    (void)x;
}

/*!
 *  \warning    函数的定义以及全部声明必须对应同一类型，但为了与C语言兼容，C++会自动忽略 \n
 *              参数类型的顶层const. 因此， fn(int x)与fn(const int x)对应的的是同一个函数。
 *              调用fn(int x)允许修改实参，fn(const int x)不允许修改实参，它们都只是调用着提供的
 *              实参的一个副本。因此调用过程不会破坏上下文的数据安全性。
 *
void fn(const int x)
{
    (void)x;
}
 *
 */

int factorial(int n)
{
#if false
    return (n > 1) ? n * factorial(n-1) : 1;
#else
    if (n > 1)
    {
        return n * factorial(n-1);
    }
    return 1;
#endif
}
