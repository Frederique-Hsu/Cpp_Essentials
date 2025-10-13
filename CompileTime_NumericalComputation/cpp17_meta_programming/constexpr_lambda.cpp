/*!
 *  \file       constexpr_lambda.cpp
 *  \brief      研究常量式lambda
 *  
 */


/*!
 *  \details    C++17 对于元编程的改进，主要在于支持常量式 lambda，即支持常量式 lambda 的编译期计算。
 *              因为 lambda 可以局部化，属于书写上比函数更优雅。
 * 
 *  \attention  lambda 的常量式作用由编译器说了算，显式常量式 lambda, 编译中可能不进行编译期计算，
 *              隐式常量式 lambda，编译中可能进行编译期计算。
 */

 /*!
  * \section    显式常量式 lambda
  */
#if false
    constexpr int y = 3;
    /*!
    *  \note   constexpr 变量不能作为被lambda表达式所捕获的对象。
    *          因为constexpr 变量没有自动存储空间。
    */
    auto fn_add = [y]() constexpr   // explicit lambda
    {
        int x = 12;
        return y + x;
    };
#endif

constexpr int add(int n)    // meta-function
{
    return [n]{ return n + 7; }();      // constexpr lambda obviously
}


/*================================================================================================*/


/*!
 *  \section    隐式常量式 lambda
 */
auto ans = [](int n)
{
    return 3 + n;
};

[[maybe_unused]] constexpr int res = ans(10);    // will compile-time calculate

auto inc = [](int n)
{
    return n + 1;
};

[[maybe_unused]] constexpr int (*ip)(int) = inc;     // become constexpr function pointer;
