/*!
 *  \file       array.hpp
 *  \brief      
 *  
 */


#pragma once

#include <stddef.h>

/* Declaration ===================================================================================*/
template<typename T, size_t N>
struct array
{
    T elem[N];

    T* begin() noexcept;
    const T* begin() const noexcept;
    T* end() noexcept;
    const T* end() const noexcept;

    constexpr size_t size() noexcept;

    T& operator[](size_t n);
    const T& operator[](size_t n) const;

    T* data() noexcept;
    const T* data() const noexcept;
};

template<typename T, size_t N> void print(array<T, N>& a);


/* Implementation ================================================================================*/
template<typename T, size_t N> 
T* array<T, N>::begin() noexcept
{
    return elem;
}

template<typename T, size_t N> 
const T* array<T, N>::begin() const noexcept
{
    return elem;
}

template<typename T, size_t N>
T* array<T, N>::end() noexcept
{
    return elem + N;
}

template<typename T, size_t N>
const T* array<T, N>::end() const noexcept
{
    return elem + N;
}

template<typename T, size_t N>
constexpr size_t array<T, N>::size() noexcept
{
    return N;
}

template<typename T, size_t N>
T& array<T, N>::operator[](size_t n)
{
    return elem[n];
}

template<typename T, size_t N>
const T& array<T, N>::operator[](size_t n) const
{
    return elem[n];
}

template<typename T, size_t N>
T* array<T, N>::data() noexcept
{
    return elem;
}

template<typename T, size_t N>
const T* array<T, N>::data() const noexcept
{
    return elem;
}

template<typename T, size_t N> void print(array<T, N>& a)
{
    for (size_t i = 0; i != a.size(); ++i)
    {
        std::cout << a[i] << std::endl;
    }
}