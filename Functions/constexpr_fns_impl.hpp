/*!
 *  \file       constexpr_fns_impl.hpp
 *  \brief
 *
 */

namespace my
{
template<typename Type>
complex<Type>::complex() : m_real(Type{}), m_imag(Type{})
{
}

template<typename Type>
complex<Type>::complex(Type real, Type imag) : m_real(real), m_imag(imag)
{
}

template<typename Type>
complex<Type>::complex(const complex<Type>& cmp) : m_real(cmp.m_real), m_imag(cmp.m_imag)
{
}

template<typename Type>
complex<Type>& complex<Type>::operator=(const complex<Type>& cmp)
{
    if (this != &cmp)
    {
        m_real = cmp.m_real;
        m_imag = cmp.m_imag;
    }
    return *this;
}

template<typename Type>
Type complex<Type>::getReal() const
{
    return m_real;
}

template<typename Type>
Type complex<Type>::getImag() const
{
    return m_imag;
}

template<typename Type>
void complex<Type>::setReal(Type real)
{
    m_real = real;
}

template<typename Type>
void complex<Type>::setImag(Type imag)
{
    m_imag = imag;
}

template<typename Type>
complex<Type> operator+(const complex<Type>& a, const complex<Type>& b)
{
    Type real = a.m_real + b.m_real;
    Type imag = a.m_imag + b.m_imag;
    return complex(real, imag);
}

template<typename Type>
complex<Type> operator-(const complex<Type>& a, const complex<Type>& b)
{
    Type real = a.m_real - b.m_real;
    Type imag = a.m_imag - b.m_imag;
    return complex(real, imag);
}

template<typename Type>
complex<Type> operator*(const complex<Type>& a, const complex<Type>& b)
{
    Type real = a.m_real * b.m_real - a.m_imag * b.m_imag;
    Type imag = a.m_real * b.m_imag + a.m_imag * b.m_real;
    return complex(real, imag);
}


}
