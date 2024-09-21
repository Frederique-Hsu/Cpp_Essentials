/*!
 *  \file       Concepts.hpp
 *  \brief      
 *  
 */


#pragma once


template<typename T> bool Copy_Equality(T x);    // 拷贝构造语义

template<typename T> bool Copy_Assign_Equality(T x, T& y);   // 拷贝赋值语义

template<typename T> bool Move_Effect(T x, T& y);    // 移动语义

template<typename T> bool Move_Assign_Effect(T x, T& y, T& z);    // 移动赋值语义 

/*!
 *  \section    Concrete Concepts
 */

template<typename T> constexpr bool Ordered();
template<typename T> constexpr bool Regular();
// template<typename T> constexpr bool Equality_Comparable();
template<typename T> constexpr bool SemiRegular();
/*!
 *  \section    Multi-argument Concepts
 */

template<typename T, typename U> constexpr bool Common();
template<typename T> constexpr bool Totally_Ordered();
template<typename T, typename U> struct Common_Type;
template<typename T, typename U> constexpr bool Has_Equal();
template<typename T, typename U> struct Equal_Result;
template<typename T, typename U> constexpr bool Has_Less();
template<typename T, typename U> struct Less_Result;
template<typename T, typename U> constexpr bool Has_Not_Equal();
template<typename T, typename U> struct Not_Equal_Result;
template<typename T> constexpr bool Boolean();
template<typename T, typename U> constexpr bool Has_Greater();
template<typename T, typename U> struct Greater_Result;
template<typename T, typename U> constexpr bool Has_Less_Equal();
template<typename T, typename U> struct Less_Equal_Result;
template<typename T, typename U> constexpr bool Has_Greater_Equal();
template<typename T, typename U> struct Greater_Equal_Result;

template<typename A, typename B> constexpr bool Equality_Comparable();

namespace my
{
    template<typename Iter, typename Val> Iter find(Iter begin, Iter end, Val elem);
}

/*!
 *  \section    Value concepts:
 */
template<int N> constexpr bool Small_Size();

constexpr int stack_limit = 2048;

template<typename T, int N> constexpr bool Stackable();     // T是正规的，且N个类型为T的元素可以存入一个小的栈中。

template<typename T, int N> struct Buffer
{
public:
    Buffer();
private:
    T m_buffer[N];
};

template<typename T, int N> void fct_check();


/*!
 *  \section        Template Definition Checking
 *  
 */

template<typename ValueType>
class ForwardIterator
{
public:
    ForwardIterator();
    ForwardIterator(const ForwardIterator&);
    ForwardIterator& operator=(const ForwardIterator&);
    virtual ~ForwardIterator();
public:
    bool operator==(const ForwardIterator&);
    bool operator!=(const ForwardIterator&);
    void operator++();
    ValueType& operator*();
};