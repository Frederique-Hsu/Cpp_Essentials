/*!
 *  \file       function_overload.hpp
 *  \brief
 *
 */


#ifndef FUNCTION_OVERLOAD_HPP
#define FUNCTION_OVERLOAD_HPP

#include <iostream>
#include <complex>

/*!
 *  \def    为不同数据类型的同一种操作起相同的名字成为重载 overloading
 */

void print(int);
void print(const char*);
void print(long);
void print(double);
// void print(short);
void print(char);

/*!
 *  \section    函数重载调用时自动解析
 *
 *  \details    当调用函数fnct时，由编译器决定使用名为fnct的重载函数组中的哪一个。
 *              依据是考察实参类型与fnct的哪个函数的形参类型最匹配。当找到最佳匹配时，就调用该函数，反之，引发编译器错误。
 *
 *  \list       自动解析重载的判定准则是：
 *
 *      \li     精确匹配
 *              即：无须类型转换或者仅需简单的类型转换即可实现匹配，如：
 *              1. 数组名转换为指针
 *              2. 函数名转换为函数指针
 *              3. T转换为const T
 *
 *      \li     执行提升后匹配
 *              即：执行了整数提升，如：
 *              1. bool转换成int
 *              2. char转换为int
 *              3. short转换成int
 *              4. 上述转换的unsigned版本
 *              5. 以及float转化为double
 *
 *      \li     执行标准类型转换后实现匹配，如：
 *              1. int转换为double
 *              2. double转换为int
 *              3. double转换为long double
 *              4. Derived*转换为Base*
 *              5. T*转换为void*
 *              6. int转换成unsigned int
 *
 *      \li     执行用户自定义的类型转换后实现匹配， 如：double转换成complex<double>
 *
 *      \li     使用函数声明中的省略号...进行匹配
 *  \endlist
 */

void print_int(int);
void print_char(char);
void print_string(const char*);

/*!
 *  \section    重载与返回类型
 *
 *  \details    在重载解析过程中不考虑函数的返回类型，这样可以确保对运算符或者调用函数调用的解析独立于上下文。如下
 *              对于sqrt的重载。 如果把返回类型也考虑在内的花，对sqrt()的重载解析就必须依赖于上下文而无法独立进行了。
 */
float sqrt(float);
double sqrt(double);


namespace my
{
/*!
 *  \remark     多实参函数重载解析
 */
                              int pow(int, int);
                           double pow(double, double);
template<class T> std::complex<T> pow(T, std::complex<T>)
{
    std::cout << "called pow<T>(T, complex<T>)" << std::endl;
    return std::complex<T>{};
}
template<class T> std::complex<T> pow(std::complex<T>, T)
{
    std::cout << "called pow<T>(complex<T>, T)" << std::endl;
    return std::complex<T>{};
}
template<class T> std::complex<T> pow(std::complex<T>, std::complex<T>)
{
    std::cout << "called pow<T>(complex<T>, complex<T>)" << std::endl;
    return std::complex<T>{};
}
}

namespace manual_overload_resultion
{
/*!
 *  \note   某个函数的重载版本过少或过多都可能导致歧义
 */
void f1(char);
void f1(int n);
void f1(long);

void f2(char*);
void f2(int*);
}

/*!
 *  \section    函数的前置和后置条件
 *
 *  \details    把函数调用时应该遵循的约定条件称为前置条件 precondition
 *              把函数返回时应该遵循的约定称为后置条件    postcondition
 */
int area(int len, int width);

#endif  /* FUNCTION_OVERLOAD_HPP */
