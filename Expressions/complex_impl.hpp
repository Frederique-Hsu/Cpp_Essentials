/*!
 *  \file       complex_impl.hpp
 *  \brief
 *
 */


/* Implementation ================================================================================*/
namespace my
{
template<typename Type> complex<Type>::complex(const Type& re, const Type& im) : real(re), imag(im)
{
}

template<typename Type>
complex<Type>::complex(const complex<Type>& rhs) : real(rhs.real), imag(rhs.imag)
{
}

template<typename Type>
complex<Type>& complex<Type>::operator=(const complex<Type>& rhs)
{
    if (this != &rhs)
    {
        real = rhs.real;
        imag = rhs.imag;
    }
    return *this;
}

template<typename Type> Type complex<Type>::getReal() const
{
    return real;
}

template<typename Type> void complex<Type>::setReal(const Type& re)
{
    real = re;
}

template<typename Type> Type complex<Type>::getImag() const
{
    return imag;
}

template<typename Type> void complex<Type>::setImag(const Type& im)
{
    imag = im;
}

constexpr complex<double>::complex(double re, double im) : m_real(re), m_imag(im)
{
}

constexpr double complex<double>::getReal() const
{
    return m_real;
}

void complex<double>::setReal(double value)
{
    m_real = value;
}

constexpr double complex<double>::getImag() const
{
    return m_imag;
}

void complex<double>::setImag(double value)
{
    m_imag = value;
}

complex<double>& complex<double>::operator=(double value)
{
    m_real = value;
    return *this;
}

complex<double>& complex<double>::operator+=(double value)
{
    m_real += value;
    return *this;
}
}
