/*!
 *  \file       user_specialization.cpp
 *  \brief      
 *  
 */


#include "user_specialization.hpp"

template<typename T>
Vector<T>::Vector() : elements{nullptr}, sz{0}
{
}

template<typename T>
Vector<T>::~Vector()
{
    if (elements != nullptr)
    {
        delete [] elements;
    }
}

template<typename T>
Vector<T>::Vector(int size) : elements{new T[size]}, sz{size}
{
}

template<typename T>
T& Vector<T>::at(int i)
{
    return elements[i];
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    return elements[index];
}

template<typename T>
int Vector<T>::size() const
{
    return sz;
}

template<typename T>
T*& Vector<T*>::at(int i)
{
    return reinterpret_cast<T*&>(Base::at(i));
}

template<typename T>
T*& Vector<T*>::operator[](int index)
{
    return reinterpret_cast<T*&>(Base::operator[](index));
}

template<typename T>
int Vector<T*>::size() const
{
    return Base::size();
}