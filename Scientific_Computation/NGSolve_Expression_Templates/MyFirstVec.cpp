/*!
 *  \file       MyFirstVec.cpp
 *  \brief      
 *  
 */


#include "MyFirstVec.hpp"

#include <algorithm>

template<typename T>
MyFirstVec<T>::MyFirstVec(int size) : sz{size}
{
    elements = new T[sz];
}

template<typename T>
MyFirstVec<T>::~MyFirstVec()
{
    if (elements != nullptr)
    {
        delete [] elements;
    }
}

template<typename T>
MyFirstVec<T>::MyFirstVec(const MyFirstVec<T>& rhs) : sz{rhs.sz}
{
    elements = new T[sz];
}

template<typename T>
int MyFirstVec<T>::Size() const
{
    return sz;
}

template<typename T>
T& MyFirstVec<T>::operator()(int index)
{
    return elements[index];
}

template<typename T>
const T& MyFirstVec<T>::operator()(int index) const
{
    return elements[index];
}

template<typename T>
MyFirstVec<T>& MyFirstVec<T>::operator=(const MyFirstVec<T>& rhs)
{
    if (this != &rhs)
    {
        sz = rhs.sz;
        if (elements != nullptr)
        {
            delete [] elements;
        }

        elements = new T[sz];
        for (int index = 0; index < sz; ++index)
        {
            elements[index] = rhs.elements[index];
        }
    }
    return *this;
}

template<typename T>
MyFirstVec<T>& MyFirstVec<T>::operator=(const T& element)
{
    for (int index = 0; index < sz; ++index)
    {
        elements[index] = element;
    }
    return *this;
}

template<typename T>
MyFirstVec<T> operator+(const MyFirstVec<T>& x, const MyFirstVec<T>& y)
{
    MyFirstVec<T> result(x.Size());
    for (int index = 0; index < x.Size(); ++index)
    {
        result(index) = x(index) + y(index);
    }
    return result;
}

template<typename T> 
MyFirstVec<T> operator*(double a, const MyFirstVec<T>& x)
{
    MyFirstVec<T> result(x.Size());
    for (int index = 0; index < x.Size(); ++index)
    {
        result(index) = x(index) * a;
    }
    return result;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const MyFirstVec<T>& w)
{
    os << "[";
    for (int index = 0; index < w.Size(); ++index)
    {
        os << w(index);
        if (index < w.Size()-1)
        {
            os << ",  ";
        }
        else
        {
            os << "]";
        }
    }
    return os;
}