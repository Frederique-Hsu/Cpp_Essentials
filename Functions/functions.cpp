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

/*!
 *  \warning    一旦函数返回了结果，所占的存储空间就被释放了。
 *              因此，不应该返回指向函数局部非static变量的指针。
 *              也不能返回函数局部非static变量的引用。
 */
int* fp()
{
    int local = 1;

    /*!
     *  \note   Address of stack memory associated with local variable `local` returned to
     *          caller.
     */
    return &local;
}

int& fr()
{
    int local = 1;

    /*!
     *  \note   Address of stack memory associated with local variable `local` returned to caller.
     */
    return local;
}

/*!
 *  \warning    而且constexpr函数的声明和实现不能分开，须放在一起。
 *              一般放在头文件，若只被同一个源文件的其他代码调用，则可以放在源文件里。
constexpr int fac(int n)
{
    return (n > 1) ? n * fac(n-1) : 1;
}
 */
