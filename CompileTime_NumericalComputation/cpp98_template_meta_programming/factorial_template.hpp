/*!
 *  \file       factorial_template.hpp
 *  \brief      
 *  
 */


#ifndef FACTORIAL_TEMPLATE_HPP
#define FACTORIAL_TEMPLATE_HPP

    /*!
     *  \brief      Sum of factorial
     *  \version    cpp98_TMP_1.0
     */
    template<int n>
    struct Factorial
    {
        static const int t = Factorial<n-1>::t * n;     // t = factorial(n)
        static const int v = Factorial<n-1>::v + t;     // v = sumOfFactorial(n)
    };

    template<>
    struct Factorial<0>     // template specialization
    {
        static const int t = 1;     // factorial(0) initial 
        static const int v = 0;     // sumOfFactorial(0) initial
    };

    void print_template_factorial();

/*================================================================================================*/

    /*!
     *  \brief      Sum of factorial
     *  \version    cpp98_TMP_2.0
     *  \details    用枚举符来表示模板中不占存储空间的整数值，同样可以表示整数常量，从而可以在编译期进行计算。
     *  \note       模板类不能包含非静态成员，否则其实例化推演过程将会产生模板类对象，而访问对象成员的操作
     *              则依赖程序运行期的内存布局，从而失去了编译期的推演资格。
     */
    template<int n>
    struct FactorialEnumerator  
    {
        enum 
        {
            t = FactorialEnumerator<n-1>::t * n,
            v = FactorialEnumerator<n-1>::v + t
        };
    };

    template<>
    struct FactorialEnumerator<0>
    {
        enum
        {
            t = 1,
            v = 0
        };
    };

    void print_template_factorial_enumerator();

#endif  /* FACTORIAL_TEMPLATE_HPP */
