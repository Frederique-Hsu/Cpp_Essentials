/*!
 *  \file   Vector.hpp
 *  \brief  Define the template of Vector, and implement it.
 *  
 */

#pragma once

#include <stdexcept>

namespace Template
{
    /* Definition ================================================================================*/
    template<typename T>
    class Vector
    {
    private:
        T*  elem;
        int sz;
    public:
        Vector(int s);
        ~Vector();

        T& operator[](int i);
        const T& operator[](int i) const;
        int size() const;

        // T* begin(Vector<T>& x);
        // T* end(Vector<T>& x);
    };

    /* Implementation ============================================================================*/
    template<typename T> Vector<T>::Vector(int s)
    {
        if (s < 0)
        {
            throw std::length_error("Negative size error");
        }
        elem = new T[s];
        sz = s;
    }

    template<typename T> Vector<T>::~Vector()
    {
        delete [] elem;
    }

    template<typename T>
    const T& Vector<T>::operator[](int i) const
    {
        if ((i < 0) || (size() <= i))
        {
            throw std::out_of_range("Vector::operator[]");
        }
        return elem[i];
    }

    template<typename T>
    T& Vector<T>::operator[](int i)
    {
        return elem[i];
    }

    template<typename T>
    int Vector<T>::size() const
    {
        return sz;
    }

    #if 0
    template<typename T>
    T* begin(Vector<T>& x)
    {
        return &x[0];
    }

    template<typename T>
    T* end(Vector<T>& x)
    {
        return x.begin() + x.size();
    }
    #endif
}

template<typename Container, typename Value>
Value sum(const Container& container, Value v)
{
    for (auto elem : container)
    {
        v += elem;
    }
    return v;
}