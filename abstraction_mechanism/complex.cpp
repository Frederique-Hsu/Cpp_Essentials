/*!
 *  \file   complex.cpp
 *  \brief  Implement the class: complex
 *  
 */


#include "complex.hpp"

#include <cmath>

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
    // static_assert((z.re != 0) || (z.im != 0), "complex z cannot be 0.");

    double denominator = std::pow(z.re, 2) + std::pow(z.im, 2);
    double real = re * z.re - im * z.im;
    double imag = im * z.re - re * z.im;

    re = real / denominator;
    im = imag / denominator;
    return *this;
}

complex operator+(complex a, complex b)
{
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