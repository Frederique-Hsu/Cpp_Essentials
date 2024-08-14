/*!
 *  \file       complex.hpp
 *  \brief
 *
 */


#pragma once

/* Prototype =====================================================================================*/
namespace my
{
template<typename Type> class complex
{
private:
    Type real;
    Type imag;
public:
    complex(const Type& re, const Type& im);
    complex(const complex<Type>& rhs);
    complex& operator=(const complex<Type>& rhs);
public:
    Type getReal() const;
    void setReal(const Type& re);
    Type getImag() const;
    void setImag(const Type& im);
};

template<> class complex<double>
{
public:
    constexpr complex(double re = 0.0, double im = 0.0);
    constexpr complex(const complex<float>&);
    explicit constexpr complex(const complex<long double>&);
private:
    double m_real;
    double m_imag;
public:
    constexpr double getReal() const;
    void setReal(double);
    constexpr double getImag() const;
    void setImag(double);

    complex<double>& operator=(double);
    complex<double>& operator+=(double);
};
}

#include "complex_impl.hpp"
