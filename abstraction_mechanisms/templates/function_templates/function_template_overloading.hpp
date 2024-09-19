/*!
 *  \file       function_template_overloading.hpp
 *  \brief      
 *  
 */


#pragma once

#include <complex>
#include <iostream>

                     double          sqrt(double);
template<typename T> T               sqrt(T);
template<typename T> std::complex<T> sqrt(std::complex<T>);

/*!
 *  \section    函数模板的重载解析规则：
 *
 *  \brief      基本原则是： 
 * 
 *              对每个模板，我们要找到对给定函数实参集合来说最佳的特例。
 * 
 *              接下来，我们对这些特例化版本和所有普通函数应用普通函数重载解析规则。
 *  \list
 *      \li     找到参与重载解析的所有函数模板特例化版本。
 * 
 *              具体方法是： 检查每个函数模板，确定如果作用域中没有其他同名函数模板或函数的话，哪些模板实参会被使用。
 *              对于调用sqrt(z), 则 sqrt<double>(complex<double>) 和 sqrt<complex<double>>(complex<double>) 将称为候选
 * 
 *      \li     如果两个函数模板都可以调用，且其中一个比另一个更特例化，则接下来的步骤只考虑最特殊化的版本。
 * 
 *              对于调用 sqrt(z)，sqrt<double>(complex<double>) 比 sqrt<complex<double>>(complex<double>) 更特例化，
 *              因为任何匹配 sqrt<T>(complex<T>) 的调用也都能匹配 sqrt<T>(T) 
 * 
 *      \li     对前两个步骤后还留在候选集中的函数模板和所有候选普通函数一起进行重载解析，方法与普通函数重载解析相同。
 * 
 *              如果一个函数模板实参是通过模板实参推断确定的，则不能再对他进行提升、标准类型转换或者用户自定义的类型转换。
 *              
 *              对 sqrt(2), sqrt<int>(int)是精确匹配，因此它优于 sqrt(double)
 * 
 *      \li     如果一个普通函数和一个特例化版本匹配得一样好，那么优先选择普通函数。
 * 
 *              因此， 对于 sqrt(2.0), sqrt(double) 优于  sqrt<double>(double)
 * 
 *      \li     如果没有发现任何匹配，则调用是错误的。如果我们最终得到多个一样好的匹配，则调用有二义性，这也是一个错误。
 *  \endlist
 */


template<typename Iter>
typename Iter::value_type mean(Iter first, Iter last)
{
    using T = typename Iter::value_type;
    
    T sum_value = T{};
    int n = 0;
    for (Iter it = first; it != last; ++it)
    {
        sum_value += *it;
        n++;
    }
    return T{sum_value / n};
}

#if true
template<typename T>
T mean(T* first, T* last)
{
    T sum_value = T{};
    int n = 0;
    for (T* it = first; it != last; ++it)
    {
        sum_value += *it;
        n++;
    }
    return T{sum_value / n};
}
#endif


/*!
 *  \note   SFINAE : Substitution Failure Is Not An Error
 *
 *  \details    在生成一个候选函数来解析一个函数调用的过程中，如果编译器发现生成一个模板特例化是无意义的，就不会将它加入
 *              重载候选集中。 如果一个模板特例化版本会导致类型错误，它就被认为是无意义的。
 * 
 *              另外，如果代入一个类型进行实例化，发现是错误的，那么即使一个函数被选为最佳匹配，仍然可能导致编译失败。
 */


/*!
 *  \section    Overloading and Derivation
 *  
 *              重载解析规则保证函数模板能完美地和继承机制结合使用
 */

template<typename T>
class Interface
{
public:
    virtual ~Interface() = default;
public:
    virtual bool execute(T num) = 0;
};

template<typename T>
class Base
{
public:
    Base(T elem);
    virtual ~Base() = default;
protected:
    T m_elem;
public:
    virtual bool execute();
};

template<typename T>
class Derived : public Base<T>
{
public:
    Derived(T elem, bool (*checking)(T));
private:
    bool (*m_checker)(T elem);
public:
    virtual bool execute() override;
};

template<typename T> bool execute(Base<T>* pobj);


/*!
 *  \section    Overloading and Non-Deduced Parameters
 */

template<typename T, typename Container> T get_nth(const Container& container, int index);

struct Index
{
    Index(int i);
    operator int();
    
    int idx;
};


/*!
 *  \section    template alias
 */

template<int>
struct int_exact_traits
{
    using type = int;
};

template<>
struct int_exact_traits<8>
{
    using type = char;
};

template<>
struct int_exact_traits<16>
{
    using type = short;
};

template<int N>
using int_exact = typename int_exact_traits<N>::type;

#include "function_template_overloading_impl.hpp"

