/*!
 *  \file       interface_specialization.hpp
 *  \brief      
 *  
 */


#pragma once

#include <vector>
#include <type_traits>

namespace my
{
template<typename T>
class complex
{
public:
    complex(const T& re = T{}, const T& im = T{});
    complex(const complex&);
    complex& operator=(const complex&);
    complex<T>& operator=(const T&);
    complex<T>& operator+=(const T&);
    template<typename U> complex(const complex<U>&);    // conversion from complex<X> to complex<T>
    template<typename U> complex<T>& operator=(const complex<U>&);
    template<typename U> complex<T>& operator+=(const complex<U>&);
    ~complex() = default;
private:
    T m_real;
    T m_imag;
public:
    T& real();
    const T& real() const;
    T& imag();
    const T& imag() const;
};

template<> class complex<float>
{
public:
    complex(float re = float{}, float im = 0.0F);
    complex(const complex&);
    complex<float>& operator=(float);
    complex<float>& operator+=(float);
    complex<float>& operator=(const complex<float>&);
private:
    float m_real;
    float m_imag;
public:
    float& real();
    const float& real() const;
    float& imag();
    const float& imag() const;
};

template<> class complex<double>
{
public:
    constexpr complex(double re = 0.0, double im = double{});
    constexpr complex(const complex<float>&);
    explicit constexpr complex(const complex<long double>&);
private:
    double m_real;
    double m_imag;
public:
    double& real();
    const double& real() const;
    double& imag();
    const double& imag() const;
};

}   // namespace my

template<typename T, int N> class Matrix    // N dimensional matrix
{
public:
    Matrix(int col_size);
    ~Matrix();
private:
    T* elements[N];     // N rows, m_cols 
    int m_cols;
public:
    int totalCount() const;
    void showLayout();
    void assign(const std::vector<T>& vec);
};

template<typename T> class Matrix<T, 0>     // N = 0 specialization, scalar
{
public:
    Matrix(T init_value);
private:
    T val;
public:
    int totalCount() const;
    void showLayout();
};

template<typename T> using Scalar = Matrix<T, 0>;

template<typename T> class Matrix<T, 1>
{
public:
    Matrix(int size);
    ~Matrix();
private:
    T* elements;
    int sz;
public:
    int totalCount() const;
    void showLayout();
    void assign(const std::vector<T>& vec);
};

template<typename T> class Matrix<T, 2>
{
public:
    Matrix(int rows, int cols);
    ~Matrix();
private:
    T* elements;
    int m_row;
    int m_col;
public:
    int totalCount() const;
    void showLayout();
    void assign(const std::vector<T>& vec);
};

/*!
 *  \section    Primary template
 */
template<typename T>    // 主模板必须在任何特例化版本之前声明
class List
{
    // static_assert(std::regular<T>(), "List<T>: T must be regular");  // 约束检查， 必须在每个特例化把那本都复制约束检查
};

template<typename T>
class List<T*>
{
};

/*================================================================================================*/

#include "interface_specialization_impl.hpp"