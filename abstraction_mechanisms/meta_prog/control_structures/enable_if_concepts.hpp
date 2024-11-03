/*!
 *  \file       enable_if_concept.hpp
 *  \brief      
 *  
 */


#pragma once

#include <type_traits>

#include "condition.hpp"

#if __cplusplus >= 202002L
    #include <concepts>
#endif

template<typename T>
constexpr bool Ordered()
{
    return std::totally_ordered<T>;
}


/*============================================================================*/

/*!
 *  \section    Prototype
 */

struct substitution_failure;    // SFINAE : substitution failure is not an error 替换失败并不是一个错误

template<typename T> struct substitution_succeeded;

template<typename T> struct get_fn_result;

template<typename T> struct has_fn;

template<typename T> constexpr bool Has_Fn()
{
    return has_fn<T>::value;
}

template<typename T> constexpr bool Has_Not_Equals()
{
    return has_fn<T>::value;
}