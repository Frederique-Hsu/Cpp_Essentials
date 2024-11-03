/*!
 *  \file       condition.cpp
 *  \brief      
 *  
 */


#include "condition.hpp"

#include <iostream>

template<typename T>
SmartPointer<T>::SmartPointer(T* ptr) : m_ptr{ptr}, ref_count{0}
{
    ref_count++;
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer& rhs) : m_ptr{rhs.m_ptr}, ref_count{rhs.ref_count}
{
    ref_count++;
}

template<typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    if (--ref_count == 0)
    {
        if (m_ptr != nullptr)
        {
            delete m_ptr;
        }
    }

    m_ptr = rhs.m_ptr;
    ref_count = rhs.ref_count;
    ref_count++;
    return *this;
}

template<typename T>
SmartPointer<T>::~SmartPointer()
{
    if (--ref_count == 0)
    {
        if (m_ptr != nullptr)
        {
            delete m_ptr;
        }
    }
}

template<typename T>
T& SmartPointer<T>::operator*()
{
    return *m_ptr;
}

template<typename T>
Enable_If<Is_Class<T>(), T*> SmartPointer<T>::operator->()
{
    return m_ptr;
}


namespace my
{
    template<typename T>
    Vector<T>::Vector(std::size_t size, const T& val) : m_elements{nullptr}, m_size{size}
    {
        std::cout << "my::Vector<T>::Vector(std""size_t size = " << size 
                  << ", const T& val = " << val << ")" << std::endl;
        m_elements = new T[size];
        for (auto index = 0U; index < size; ++index)
        {
            *(m_elements + index) = val;
        }
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        if (m_elements != nullptr)
        {
            delete m_elements;
        }
    }

    template<typename T> 
    template<typename Iter, typename>
    Vector<T>::Vector(Iter begin, Iter end) : m_elements{nullptr}, m_size{static_cast<std::size_t>(end - begin)}
    {
        std::cout << "my::Vector<T>::Vector(Iter begin, Iter end)" << std::endl;
        m_elements = new T[m_size];

        int index = 0;
        for (Iter it = begin; it != end; ++it)
        {
            *(m_elements + index++) = *it;
        }
    }

    template<typename T>
    T* Vector<T>::begin()
    {
        return m_elements;
    }

    template<typename T>
    T* Vector<T>::end()
    {
        return m_elements + m_size;
    }
}