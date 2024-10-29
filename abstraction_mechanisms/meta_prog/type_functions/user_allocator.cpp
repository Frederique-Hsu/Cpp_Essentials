/*!
 *  \file       user_allocator.cpp
 *  \brief
 *
 */


#include "user_allocator.hpp"


template<typename T>
OnHeap<T>::OnHeap() : ptr{new T}
{
}

template<typename T>
OnHeap<T>::~OnHeap()
{
    if (ptr != nullptr)
    {
        delete ptr;
    }
}

template<typename T>
T& OnHeap<T>::operator*()
{
    return *ptr;
}

template<typename T>
T* OnHeap<T>::operator->()
{
    return ptr;
}

template<typename T>
Scoped<T>::Scoped(const T& value) : x{value}
{
}

template<typename T>
T& Scoped<T>::operator*()
{
    return x;
}

template<typename T>
T* Scoped<T>::operator->()
{
    return &x;
}