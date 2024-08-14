/*!
 *  \file       constexpr_functions.hpp
 *  \brief
 *
 */


#pragma once


/*!
 *  \section    constexpr函数
 *
 *  \details    通常情况下，函数无法在编译时求值，因此就不能在常量表达式中被调用。
 *              但是通过将函数指定为constexpr，我们就能向编译器传递这样的信息，即：
 *              如果给定了常量表达式作为实参，则希望该函数能被用在常量表达式中，在编译时进行计算。
 *
 *              和内联函数一样，constexpr函数遵循ODR(一次定义法则)，因此，多个编译单元中的定义必须保持严格一致。
 */

constexpr int factorial(int n)
{
    /*!
     *  \warning    constexpr函数一般不宜Prototype跟Implementation分开，直接合在一起。
     *              不然编译器会报错。
     */
    return (n > 1) ? n * factorial(n-1) : 1;
}

constexpr void bad1(int a);
constexpr int bad2(int a);
constexpr int bad3(int a);


namespace my
{
    /*! \section    Prototype */
    template<typename Type> class complex
    {
    public:
        explicit complex(Type real, Type imag);
        complex(const complex& rhs);
        complex& operator=(const complex& rhs);
    private:
        Type m_real;
        Type m_imag;
    public:
        Type getReal() const;
        Type getImag() const;
    };

    template<> class complex<float>
    {
    public:
        constexpr complex(float real = 0.0, float imag = 0.0) : m_real(real), m_imag(imag)
        {
        }
        explicit constexpr complex(const complex<double>& rhs)
        {
            m_real = static_cast<float>(rhs.getReal());
            m_imag = static_cast<float>(rhs.getImag());
        }
    private:
        float m_real{};
        float m_imag{};
    };

    /*!
     *  \remark     constexpr函数可以返回一个引用或指针，但是这种做法违背了constexpr函数作为常量表达式求值要件的初衷。
     *              因为这就很难判定此类函数的返回结果是否是一个常量表达式。
     */
    constexpr const int* addr(const int& r)
    {
        return &r;
    }

    /*============================================================================================*/

    /*! \section    Implementation */
    template<typename Type> complex<Type>::complex(Type real, Type imag) : m_real{real}, m_imag{imag}
    {
    }

    template<typename Type> complex<Type>::complex(const complex<Type>& rhs)
    {
        if (this != &rhs)
        {
            m_real = rhs.m_real;
            m_imag = rhs.m_imag;
        }
    }

    template<typename Type> complex<Type>& complex<Type>::operator=(const complex<Type>& rhs)
    {
        if (this != &rhs)
        {
            m_real = rhs.m_real;
            m_imag = rhs.m_imag;
        }
        return *this;
    }

    template<typename Type> Type complex<Type>::getReal() const
    {
        return m_real;
    }

    template<typename Type> Type complex<Type>::getImag() const
    {
        return m_imag;
    }
}
