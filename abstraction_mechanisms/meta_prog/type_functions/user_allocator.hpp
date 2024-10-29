/*!
 *  \file       user_allocator.hpp
 *  \brief
 *
 */


#pragma once


#include <string>
#include <type_traits>

/*!
 *  \section    Design a user-specific allocator
 *
 *  \brief      设计一个分配器，想要在栈中为小对象分配内存，而在堆中（自由存储空间）为大对象分配内存。
 *
 */

constexpr int on_stack_max = sizeof(std::string);

template<typename T> class Scoped;

template<typename T> class OnHeap;

template<typename T>
struct ObjHolder
{
    using type = typename std::conditional<
        (sizeof(T) <= on_stack_max), Scoped<T>, OnHeap<T>>::type;
};


template<typename T>
class OnHeap
{
public:
    // using type = T*;
public:
    OnHeap();
    ~OnHeap();

    OnHeap(const OnHeap&) = delete;     // prevent from copying
    OnHeap& operator=(const OnHeap&) = delete;
private:
    T* ptr;
public:
    T& operator*();
    T* operator->();
};


template<typename T>
class Scoped
{
public:
    // using type = T;
public:
    Scoped(const T& value = T{});
    Scoped(const Scoped&) = delete;
    Scoped& operator=(const Scoped&) = delete;
private:
    T x;
public:
    T& operator*();
    T* operator->();
};

/*!
 *  \section    Type Alias
 */

template<typename T>
using Holder = typename ObjHolder<T>::type;

template<bool Cond, typename T, typename F>
using Conditional = typename std::conditional<Cond, T, F>::type;

    template<typename T> using Error = void*;

    template<typename T>
    using MyType = typename std::conditional<std::is_integral<T>::value,
                                             std::make_unsigned<T>,
                                             Error<T>>::type;

    template<typename T>
    using Make_Unsigned = typename std::make_unsigned<T>::type;

    template<template<typename...> class F, typename... Args>
    using Delay = F<Args...>;

    template<typename T>
    using MyConditionalType = typename std::conditional<std::is_integral<T>::value,
                                                        Delay<Make_Unsigned, T>,
                                                        Error<T>>::type;