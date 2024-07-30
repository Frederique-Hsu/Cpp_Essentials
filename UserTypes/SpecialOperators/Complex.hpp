/*!
 *  \file       Complex.hpp
 *  \brief
 *
 */


#pragma once

#include <cmath>
#include <iostream>

template<class T> class Complex
{
public:
    Complex(const T& real = T{}, const T& imag = T{});
    Complex(const T& imag);
private:
    T m_real;
    T m_imag;
public:
    Complex<T>& operator+=(const T& real);

    T& real();
    T& imag();

    const T& real() const;
    const T& imag() const;
};

template<class T> std::ostream& operator<<(std::ostream& os, const Complex<T>& obj);
template<class T> std::istream& operator>>(std::istream& is,       Complex<T>& obj);
template<class T> Complex<T> operator+(const Complex<T>& a, const Complex<T>& b);
template<class T> Complex<T> operator-(const Complex<T>& a, const Complex<T>& b);
template<class T> Complex<T> operator*(const Complex<T>& a, const Complex<T>& b);
template<class T> Complex<T> operator/(const Complex<T>& a, const Complex<T>& b);
template<class T> Complex<T> operator+(const Complex<T>& a, const T& real);
template<class T> Complex<T> operator+(const T& real, const Complex<T>& obj);
template<class T> T mod(const Complex<T>& obj);

constexpr Complex<double> operator"" _i(long double value)
{
    return Complex<double>{0, value};
}


/*================================================================================================*/


template<class T> Complex<T>::Complex(const T& real, const T& imag) : m_real{real}, m_imag{imag}
{
}

template<class T> Complex<T>::Complex(const T& imag) : m_real{T{}}, m_imag{imag}
{
}

template<class T> T& Complex<T>::real()
{
    return m_real;
}

template<class T> T& Complex<T>::imag()
{
    return m_imag;
}

template<class T> const T& Complex<T>::real() const
{
    return m_real;
}

template<class T> const T& Complex<T>::imag() const
{
    return m_imag;
}

template<class T> Complex<T>& Complex<T>::operator+=(const T& real)
{
    m_real += real;
    return *this;
}

template<class T> std::ostream& operator<<(std::ostream& os, const Complex<T>& obj)
{
    os << obj.real();

    if (obj.imag() > T{0})
    {
        os << "+" << obj.imag() << "i" << std::endl;
    }
    else
    {
        os << obj.imag() << "i" << std::endl;
    }
    return os;
}

template<class T> std::istream& operator>>(std::istream& is, Complex<T>& obj)
{
    std::cout << "Complex' real part: ";
    is >> obj.real();
    std::cout << "and imag part: ";
    is >> obj.imag();
    return is;
}

template<class T> Complex<T> operator+(const Complex<T>& a, const Complex<T>& b)
{
    T real = a.real() + b.real();
    T imag = a.imag() + b.imag();
    return Complex<T>(real, imag);
}

template<class T> Complex<T> operator-(const Complex<T>& a, const Complex<T>& b)
{
    T real = a.real() - b.real();
    T imag = a.imag() - b.imag();
    return Complex<T>(real, imag);
}

template<class T> Complex<T> operator*(const Complex<T>& a, const Complex<T>& b)
{
    T real = a.real() * b.real() - a.imag() * b.imag();
    T imag = a.real() * b.imag() + a.imag() * b.real();
    return Complex<T>(real, imag);
}

template<class T> Complex<T> operator/(const Complex<T>& a, const Complex<T>& b)
{
    T denominator = std::pow(b.real(), 2) + std::pow(b.imag(), 2);
    // T numerator;

    T real = (a.real() * b.real() + a.imag() * b.imag()) / denominator;
    T imag = (a.imag() * b.real() - a.real() * b.imag()) / denominator;
    return Complex<T>(real, imag);
}

template<class T> T mod(const Complex<T>& obj)
{
    return std::sqrt(std::pow(obj.real(), 2) + std::pow(obj.imag(), 2));
}

template<class T> Complex<T> operator+(const Complex<T>& a, const T& real)
{
    T real_part = a.real() + real;
    T imag_part = a.imag();
    return Complex<T>(real_part, imag_part);
}

template<class T> Complex<T> operator+(const T& real, const Complex<T>& obj)
{
    T real_part = real + obj.real();
    T imag_part = obj.imag();
    return Complex<T>(real_part, imag_part);
}