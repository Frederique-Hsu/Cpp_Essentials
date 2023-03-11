/*!
 *  \file   complex.hpp
 *  \brief  Design the class: complex
 *
 */


#pragma once

class complex
{
public:
    complex(double r, double i) : re{i}, im{i}
    {
    }
    complex(double r) : re{r}, im{0}
    {
    }
    complex() : re{0}, im{0}
    {
    }
    
    double real() const
    {
        return re;
    }
    void real(double d)
    {
        re = d;
    }
    double imag() const
    {
        return im;
    }
    void imag(double d)
    {
        im = d;
    }
    complex& operator+=(complex z)
    {
        re += z.re;
        im += z.im;
        return *this;
    }
    complex& operator-=(complex z)
    {
        re -= z.re;
        im -= z.im;
        return *this;
    }
    complex& operator*=(complex);
    complex& operator/=(complex);
private:
    double re;
    double im;
};

bool operator==(complex a, complex b);
bool operator!=(complex a, complex b);
complex operator+(complex a, complex b);
complex operator-(complex a, complex b);
complex operator-(complex a);
complex operator*(complex a, complex b);
complex operator/(complex a, complex b);