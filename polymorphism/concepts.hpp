/*!
 *  \file       concepts.hpp
 *  \brief      
 *  
 */


#pragma once

#include <type_traits>

/*!
 *  \attention  concept was supported after C++20
 */
template<typename T>
concept is_numeric = std::is_integral_v<T>;     // judge whether the given T is  an integral type or not.

/* use requires before the function */
template<typename T>
requires is_numeric<T>
void foo1(T t)
{
    (void)t;
}

/* use requires after the function */
template<typename T>
void foo2(T t) requires is_numeric<T>
{
    (void)t;
}

/* use the concept as template argument */
template<is_numeric T>
void foo3(T t)
{
    (void)t;
}

/* use the concept in combination with auto as argument */
void foo4(is_numeric auto t)
{
    (void)t;
}

template<typename T>
concept has_increment = requires(T t)
{
    t++;
    ++t;
};

template<has_increment T>
void foo5(T t)
{
    (void)t;
}

struct bar
{
};