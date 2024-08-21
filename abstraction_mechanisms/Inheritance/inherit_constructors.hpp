/*!
 *  \file       inheriting_constructors.hpp
 *  \brief      
 *  
 */


#pragma once

#include <vector>
#include <stdexcept>


template<typename T>
struct Vector : std::vector<T>
{
    using std::vector<T>::vector;   // Inheriting the base class constructor
    // using std::vector<T>::~std::vector<T>;   // But never inheriting the base class destructor

    T& operator[](typename std::vector<T>::size_type index);
    const T& operator[](typename std::vector<T>::size_type index) const;

private:
    void check(typename std::vector<T>::size_type index);
};


/*============================================================================*/

template<typename T>
T& Vector<T>::operator[](typename std::vector<T>::size_type index)
{
    check(index);

    return this->at(index);
}

template<typename T>
const T& Vector<T>::operator[](typename std::vector<T>::size_type index) const
{
    check(index);
    return at(index);
}

template<typename T>
void Vector<T>::check(typename std::vector<T>::size_type index)
{
    if (this->size() < index)
    {
        throw std::range_error("Vector::check() failed!");
    }
}