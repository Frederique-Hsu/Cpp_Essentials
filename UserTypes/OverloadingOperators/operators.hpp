/*!
 *  \file       operators.hpp
 *  \brief
 *
 */


#pragma once

#include <iostream>

class complex
{
    friend bool operator==(const complex& a, const complex& b);
    friend bool operator!=(const complex& a, const complex& b);
    friend std::ostream& operator<<(std::ostream& os, const complex& obj);
    friend std::istream& operator>>(std::istream& is, complex& obj);
public:
    constexpr complex(double real = 0.0, double imag = 0.0) : m_real{real}, m_imag{imag}
    {
    }

private:
    double m_real;
    double m_imag;

public:
    complex& operator+=(const complex&);
    complex& operator+=(double a);
    complex operator*(const complex&);

    constexpr double real() const;
    constexpr double imag() const;

    void real(double real);
    void imag(double imag);
};

complex operator+(complex a, complex b);
complex operator+(complex a, double b);
complex operator+(double a, complex b);

complex operator-(complex);
complex operator+(complex);

double sqrt(complex a);
complex polar(double rho, double delta);
complex conj(complex);
double abs(complex);
double arg(complex);
double norm(complex);

double real(complex);
double imag(complex);

complex acos(complex);
complex asin(complex);
complex atan(complex);

/*!
 *  \attention  When constructors are simple and inline, and especially when they are constexpr,
 *              it is quite reasonable to think of constructor invocations with literal arguments
 *              as literals.
 *
 *  \def        It is possible to go further and introduce a user-defined literal
 *              define i to be a suffix meaning "imageinary"
 */
constexpr complex operator "" i(long double d)
{
    return complex{0, static_cast<double>(d)};
}

enum Day
{
    Sun,
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat
};

Day& operator+(Day& d);
