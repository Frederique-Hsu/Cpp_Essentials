/*!
 *  \file   complex.cpp
 *  \brief  Implement the class: complex
 *  
 */


#include "complex.hpp"

#include <cmath>

bool operator==(complex a, complex b)
{
    return ((a.real() == b.real()) && (a.imag() == b.imag()));
}

bool operator!=(complex a, complex b)
{
    return !(a == b);
}

complex& complex::operator*=(complex z)
{
    double real = re * z.re - im * z.im;
    double imag = re * z.im + im * z.re;
    re = real;
    im = imag;
    return *this;
}

complex& complex::operator/=(complex z)
{
    double denominator = std::pow(z.re, 2) + std::pow(z.im, 2);
    double real = re * z.re - im * z.im;
    double imag = im * z.re - re * z.im;

    re = real / denominator;
    im = imag / denominator;
    return *this;
}

complex operator+(complex a, complex b)
{
    /* 此处利用了C++的一个特性，即：以传值方式传递实参实际上是把一份副本传递给函数，
     * 因此我们修改形参（副本）不会影响主调函数的实参，并可以将结果作为作为返回值。
     */
    return a += b;
}

complex operator-(complex a, complex b)
{
    return a -= b;
}

complex operator-(complex a)
{
    return {-a.real(), -a.imag()};
}

complex operator*(complex a, complex b)
{
    return a *= b;
}

complex operator/(complex a, complex b)
{
    return a /= b;
}