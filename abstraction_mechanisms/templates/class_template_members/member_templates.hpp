/*!
 *  \file       member_templates.hpp
 *  \brief      
 *  
 */


#pragma once


template<typename Scalar>
class Complex
{
private:
    Scalar m_real;
    Scalar m_imag;
public:
    Complex();
    template<typename T> Complex(T re, T im);
    Complex(const Complex&) = default;
    template<typename T> Complex(const Complex<T>& rhs);
public:
    Scalar& real();
    const Scalar& real() const;
    Scalar& imag();
    const Scalar& imag() const;
};

class Shape
{
public:
    // template<typename T> virtual bool intersect(const T&) const = 0;    // Error: template cannot be 'virtual'
};

#include "member_templates_impl.hpp"