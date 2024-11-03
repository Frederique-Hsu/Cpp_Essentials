/*!
 *  \file       type_predicates.hpp
 *  \brief      
 *  
 */


#pragma once


#include <type_traits>
#include <cstring>

#include "user_allocator.hpp"
#include "user_allocator.cpp"

/*!
 *  \section    Type Predicates 类型谓词， 谓词是返回布尔值的函数
 */

template<typename T>
void copy(T* dest, const T* src, int n)
{
#if defined (CHOOSE_GCC)
    for (int index = 0; index < n; ++index)
    {
        dest[index] = src[index]; 
    }
#else   // if defined (CHOOSE_CLANG)
    // if (std::is_pod<T>::value)
    if (std::is_standard_layout<T>::value && std::is_trivial<T>::value)
    {
        std::memcpy(dest, src, n * sizeof(T));
    }
    else
    {
        for (int index = 0; index < n; ++index)
        {
            dest[index] = src[index];
        }
    }
#endif
}

namespace Estd
{
    template<typename T>
    constexpr bool Is_Pod()
    {
    #if __cplusplus <= 201703L
        return std::is_pod<T>::value;
    #elif __cplusplus >= 202002L
        return std::is_standard_layout<T>::value && std::is_trivial<T>::value;
    #endif
    }

    template<typename T>
    constexpr bool Is_Big()
    {
        return 100 < sizeof(T);
    }

    template<typename T>
    constexpr bool Is_Polymorphic()
    {
        return std::is_polymorphic<T>::value;
    }
}

template<typename T>
using Obj_Holder = Conditional<Estd::Is_Big<T>(), Scoped<T>, OnHeap<T>>;