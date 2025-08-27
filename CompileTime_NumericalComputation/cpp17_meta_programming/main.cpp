/*!
 *  \file       main.cpp
 *  \brief      研究C++17的元编程
 *  
 */


#include <iostream>

#include "meta_lambda.hpp"

#define JUDGE_COMPILE_TIME_CALCULATION          1
#define JUDGE_NON_COMPILE_TIME_CALCULATION      2
#define JUDGE                                   JUDGE_COMPILE_TIME_CALCULATION

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    static_assert(__cplusplus == 201703L, "The C++ standard no. you selected is incorrect.");
    
    // access_constexpr_lambda();
    lambda_capture_data();

#if false
    constexpr int w[13] = {0};
    /*!
     *  \attention  C++17 的 lambda 表达式不需要显式说明 constexpr，只要符合常量式条件，就会进入编译期计算。
     *              但此处的 lambda 却非编译期计算，因为 C++17 的 lambda 不能捕捉常量式数据，编译裁定为 非constexpr
     */
    [p = w]() constexpr
    {
        int fact = 1;
        for (int i = 1; i < 13; ++i)
        {
            fact *= i;
            p[i] = p[i-1] + fact;   // Error: Read-only variable is not assignable
        }
    }();
#endif

#if (JUDGE == JUDGE_NON_COMPILE_TIME_CALCULATION)
    /*!
     *  \attention  如果直接将 lambda fn 用变量参数调用，那么编译器仍会将 lambda fn 当作 非constexpr 处理。
     *              其调用就不会在编译期计算。 如下代码片段：
     */
    auto fn = [](int n)
    {
        int sum = 0;
        int fact = 1;
        for (int i = 1; i <= n; ++i)
        {
            fact *= i;
            sum += fact;
        }
        return sum;
    };
    for (int n; std::cin >> n; )
    {
        std::cout << "fn(" << n << ") = " << fn(n) << std::endl;
    }
#elif (JUDGE == JUDGE_COMPILE_TIME_CALCULATION)
    /*!
     *  \attention  Lambda 函数的 constexpr 特性由编译器裁定，即使不修饰 constexpr, 只要参数是常量，只要
     *              是常量式计算，只要供常量式使用，那么该 lambda 就是 constexpr 的，如下代码片段：
     */
    auto fn = [](int n)
    {
        int sum = 0;
        int fact = 1;
        for (int i = 1; i < n; ++i)
        {
            fact *= i;
            sum += fact;
        }
        return sum;
    };

    constexpr int array[] = {     0,  fn(1),  fn(2), fn(3), fn(4),
                              fn(5),  fn(6),  fn(7), fn(8), fn(9),
                             fn(10), fn(11), fn(12)};
    for (int n; std::cin >> n; )
    {
        std::cout << "array[" << n << "] = " << array[n] << std::endl;
    }
#endif
    
    return 0;
}
