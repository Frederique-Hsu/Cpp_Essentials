/*!
 *  \file       MyVector.hpp
 *  \brief      
 *  
 */


#pragma once

#include <cstddef>

#include <iostream>
#include <initializer_list>

/*!
 *  \section    template declaration
 */
template<typename T> class MyVector;


/*!
 *  \section    template definition
 */
template<typename T>
class MyVector
{
public:
    using value_type = T;
    using reference = T&;
    using iterator = T*;
public:
    MyVector();
    explicit MyVector(const std::size_t size);
    MyVector(const MyVector& rhs);
    MyVector& operator=(const MyVector& rhs);
    MyVector(MyVector&& rhs);
    MyVector& operator=(MyVector&& rhs);
    MyVector(const std::initializer_list<T>& init_list);
    ~MyVector();
private:
    T* m_elements;
    std::size_t m_size;
public:
    T& operator[](int index);
    const T& operator[](int index) const;
    std::size_t size() const;
    iterator begin();
    iterator end();
    T* find(T target_elem);
};


/*!
 *  \section    template specialization
 */



#include "MyVector_impl.hpp"