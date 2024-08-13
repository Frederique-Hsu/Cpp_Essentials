/*!
 *  \file   Vector.cpp
 *  \brief  
 *  
 */


#include "Vector.hpp"

#include <stdexcept>

namespace CopyMove
{
    Vector::Vector(const Vector& a) : elem(new double[a.sz]), sz(a.sz)
    {
        for (int index = 0; index != sz; ++index)
        {
            elem[index] = a.elem[index];
        }
    }

    Vector::~Vector()
    {
        delete [] elem;
    }

    Vector::Vector(int s) : elem(new double[s]), sz(s)
    {
        for (int index = 0; index != sz; ++index)
        {
            elem[index] = 0;
        }
    }

    Vector& Vector::operator=(const Vector& a)
    {
        double* p = new double[a.sz];
        for (int index = 0; index != a.sz; ++index)
        {
            p[index] = a.elem[index];
        }
        delete [] elem;     /* delete the old elements */
        elem = p;
        sz = a.sz;
        return *this;
    }

    double& Vector::operator[](int i)
    {
        return elem[i];
    }

    const double& Vector::operator[](int i) const
    {
        return elem[i];
    }

    int Vector::size() const
    {
        return sz;
    }

    Vector::Vector(Vector&& a) : elem(a.elem),  /* 从a中“夺取元素” */
                                 sz(a.sz)
    {
        a.elem = nullptr;       /* 现在a中已经没有元素了 */
        a.sz = 0;
    }

    Vector& Vector::operator=(Vector&& a)
    {
        elem = a.elem;
        sz = a.sz;

        a.elem = nullptr;
        a.sz = 0;

        return *this;
    }

    Vector operator+(const Vector& a, const Vector& b)
    {
        if (a.size() != b.size())
        {
            throw std::length_error("two different length of Vectors.");
        }
        Vector result(a.size());
        for (int index = 0; index != a.size(); ++index)
        {
            result[index] = a[index] + b[index];
        }
        return result;
    }
}