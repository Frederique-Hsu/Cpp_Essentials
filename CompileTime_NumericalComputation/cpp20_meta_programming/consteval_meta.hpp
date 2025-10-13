/*!
 *  \file       consteval_meta.hpp
 *  \brief      使用C++20的 consteval 强化纠错编译期计算
 *  
 */


#pragma once


/*!
 *  \brief  显式说明为 consteval 的元函数，
 *          若使用C++20标准的编译通过，则确定该函数在编译期计算。
 */
consteval int factorial_sum(int n);


class FactorialSum
{
public:
    consteval FactorialSum();
    
private:
    int sum[13] = {0};
    
public:
    int operator[](int i) const;
};


void access_consteval_object();


/*!
 *  \details    常量式求值 (consteval) 函数， 常量式 (constexpr)  函数
 *
 *  \li         constexpr 是 C++11 最先推出的修饰符，当修饰函数时，成为常量式函数，
 *              其扮演一个提交给编译器裁定是否在编译期计算的函数。
 * 
 *  \li         consteval 是 C++20 改进的元函数，常量式对象、常量式lambda修饰符，其指示编译器必须在编译期
 *              进行计算。 consteval 从字面上译作“常值”，分别有常值函数，常值对象、常值lambda，亦表示其结果
 *              是常值。 常量表达式 (constexpr) 的结果也是常值。
 */