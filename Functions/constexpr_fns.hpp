/*!
 *  \file       constexpr_fns.hpp
 *  \brief      Make a full comprehensive research on the constexpr functions.
 *  \author     Frederique Hsu
 *  \date       Sat.    02 Spe. 2023
 *
 */


#pragma once

#include <cstddef>
#include <stdexcept>

constexpr int fib_table[] = {1, 1, 2, 3, 5, 8, 13, 21};

constexpr int fibonacci(std::size_t n)
{
    return (n < sizeof(fib_table)/sizeof(*fib_table)) ? fib_table[n] : fibonacci(n-1);
}

namespace my
{
template<typename Type> class complex
{
public:
    complex();
    complex(Type real, Type imag);
    complex(const complex<Type>& cmp);
    complex& operator=(const complex<Type>& cmp);
public:
    Type getReal() const;
    Type getImag() const;
    void setReal(Type real);
    void setImag(Type imag);

    friend complex<Type> operator+(const complex<Type>& a, const complex<Type>& b);
    friend complex<Type> operator-(const complex<Type>& a, const complex<Type>& b);
    friend complex<Type> operator*(const complex<Type>& a, const complex<Type>& b);
    friend complex<Type> operator/(const complex<Type>& a, const complex<Type>& b);
private:
    Type m_real;
    Type m_imag;
};

template<> class complex<float>
{
public:
    explicit constexpr complex(const complex<double>&);
};
}

constexpr const int* addr(const int& r)
{
    return &r;
}

const int low = 5, high = 20;

constexpr int check(int i)
{
    return ((low < i) && (i < high)) ? i : throw std::out_of_range("");
}

#include "constexpr_fns_impl.hpp"
