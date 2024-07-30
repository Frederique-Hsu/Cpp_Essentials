/*!
 *  \file       operators.cpp
 *  \brief
 *
 */


#include "operators.hpp"

#include <cmath>


inline constexpr double complex::real() const
{
    return m_real;
}

inline constexpr double complex::imag() const
{
    return m_imag;
}

void complex::real(double real)
{
    m_real = real;
}

void complex::imag(double imag)
{
    m_imag = imag;
}

complex complex::operator*(const complex& b)
{
    complex result;

    result.m_real = m_real * b.m_real - m_imag * b.m_imag;
    result.m_imag = m_real * b.m_imag + m_imag * b.m_real;

    return result;
}

bool operator==(const complex& a, const complex& b)
{
    return (a.m_real == b.m_real) and (a.m_imag == b.m_imag);
}

inline complex& complex::operator+=(const complex& b)
{
    m_real += b.m_real;
    m_imag += b.m_imag;
    return *this;
}

inline complex& complex::operator+=(double a)
{
    m_real += a;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const complex& obj)
{
    os << "complex: " << obj.m_real
       << ((obj.m_imag >= 0) ? "+" : "") << obj.m_imag << "i"
       << std::endl;
    return os;
}

complex operator+(complex a, complex b)
{
    return a += b;
}

complex operator+(complex a, double b)
{
    return complex{a.real() + b, a.imag()};
}

complex operator+(double a, complex b)
{
    return complex{a + b.real(), b.imag()};
}

double sqrt(complex a)
{
    return std::sqrt(std::pow(a.real(), 2) + std::pow(a.imag(), 2));
}

Day& operator+(Day& d)
{
    return d = (Day::Sat == d) ? Day::Sun : static_cast<Day>(d + 1);
}