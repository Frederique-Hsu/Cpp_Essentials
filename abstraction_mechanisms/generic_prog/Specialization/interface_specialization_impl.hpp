/*!
 *  \file       interface_specialization.cpp
 *  \brief      
 *  
 */


#include <iostream>
#include <iomanip>
#include <ios>
#include <vector>

namespace my
{
    template<typename T>
    complex<T>::complex(const T& re, const T& im) : m_real{re}, m_imag{im}
    {
    }

    template<typename T>
    complex<T>::complex(const complex& rhs) : m_real{rhs.m_real}, m_imag{rhs.m_imag}
    {
    }
    
    template<typename T>
    complex<T>& complex<T>::operator=(const complex& rhs)
    {
        if (this != &rhs)
        {
            m_real = rhs.m_real;
            m_imag = rhs.m_imag;
        }
        return *this;
    }
    
    template<typename T>
    complex<T>& complex<T>::operator=(const T& number)
    {
        m_real = number;
        m_imag = number;
        return *this;
    }
    
    template<typename T>
    complex<T>& complex<T>::operator+=(const T& number)
    {
        m_real += number;
        return *this;
    }
    
    template<typename T>
    inline T& complex<T>::real()
    {
        return m_real;
    }
    
    template<typename T>
    inline const T& complex<T>::real() const
    {
        return m_real;
    }
    
    template<typename T>
    inline T& complex<T>::imag()
    {
        return m_imag;
    }
    
    template<typename T>
    inline const T& complex<T>::imag() const
    {
        return m_imag;
    }
    
    template<typename T> template<typename U>
    complex<T>::complex(const complex<U>& rhs) : m_real{static_cast<T>(rhs.real())}, m_imag{static_cast<T>(rhs.imag())}
    {
    }
    
    template<typename T> template<typename U>
    complex<T>& complex<T>::operator=(const complex<U>& rhs)
    {
        m_real = static_cast<T>(rhs.real());
        m_imag = static_cast<T>(rhs.imag());
        return *this;
    }
    
    template<typename T> template<typename U>
    complex<T>& complex<T>::operator+=(const complex<U>& rhs)
    {
        m_real += static_cast<T>(rhs.real());
        m_imag += static_cast<T>(rhs.imag());
        return *this;
    }
    
    complex<float>::complex(float re, float im) : m_real{re}, m_imag{im}
    {
    }
    
    complex<float>::complex(const complex& rhs) : m_real{rhs.m_real}, m_imag{rhs.m_imag}
    {
    }
    
    complex<float>& complex<float>::operator=(float number)
    {
        m_real = number;
        m_imag = number;
        return *this;
    }
    
    inline float& complex<float>::real()
    {
        return m_real;
    }
    inline const float& complex<float>::real() const
    {
        return m_real;
    }
    inline float& complex<float>::imag()
    {
        return m_imag;
    }
    inline const float& complex<float>::imag() const
    {
        return m_imag;
    }
    
    complex<float>& complex<float>::operator+=(float number)
    {
        m_real += number;
        return *this;
    }
    
    complex<float>& complex<float>::operator=(const complex<float>& rhs)
    {
        if (this != &rhs)
        {
            m_real = rhs.m_real;
            m_imag = rhs.m_imag;
        }
        return *this;
    }
    
    constexpr complex<double>::complex(double re, double im) : m_real{re}, m_imag{im}
    {
    }
    
    constexpr complex<double>::complex(const complex<float>& rhs) 
        : m_real{static_cast<double>(rhs.real())}, m_imag{static_cast<double>(rhs.imag())}
    {
    }
    
    constexpr complex<double>::complex(const complex<long double>& rhs)
        : m_real{static_cast<double>(rhs.real())}, m_imag{static_cast<double>(rhs.imag())}
    {
    }
    
    inline double& complex<double>::real()
    {
        return m_real;
    }
    inline const double& complex<double>::real() const
    {
        return m_real;
    }
    inline double& complex<double>::imag()
    {
        return m_imag;
    }
    inline const double& complex<double>::imag() const
    {
        return m_imag;
    }
}


template<typename T, int N>
Matrix<T, N>::Matrix(int col_size) : m_cols{col_size}
{
    for (int index = 0; index < N; ++index)
    {
        elements[index] = new T[col_size];
    }
}

template<typename T, int N>
Matrix<T, N>::~Matrix()
{
    for (int index = 0; index < N; ++index)
    {
        if (elements[index] != nullptr)
        {
            delete [] (elements[index]);
        }
    }
}

template<typename T>
Matrix<T, 0>::Matrix(T init_value) : val{init_value}
{
}

template<typename T>
Matrix<T, 1>::Matrix(int size) : elements{new T[size]}, sz{size}
{
}

template<typename T>
Matrix<T, 1>::~Matrix()
{
    if (elements != nullptr)
    {
        delete [] elements;
    }
}

template<typename T>
Matrix<T, 2>::Matrix(int rows, int cols) : elements{new T[rows * cols]}, m_row{rows}, m_col{cols}
{
}

template<typename T>
Matrix<T, 2>::~Matrix()
{
    if (elements != nullptr)
    {
        delete [] elements;
    }
}

template<typename T, int N>
int Matrix<T, N>::totalCount() const
{
    return N * m_cols;
}

template<typename T>
int Matrix<T, 0>::totalCount() const
{
    return 1;
}

template<typename T>
int Matrix<T, 1>::totalCount() const
{
    return sz;
}

template<typename T>
int Matrix<T, 2>::totalCount() const
{
    return m_row * m_col;
}

template<typename T, int N>
void Matrix<T, N>::showLayout()
{
    std::cout << std::setw(8) << std::right << " " << "\t";
    
    for (int col_index = 1; col_index <= m_cols; ++col_index)
    {
        std::cout << std::setw(8) << std::right << " col. #" << col_index << "\t";
    }
    std::cout << std::endl;
    
    for (int row_index = 0; row_index < N; ++row_index)
    {
        std::cout << std::setw(8) << std::left << "row. #" << row_index+1 << "\t";
        for (int col_index = 0; col_index < m_cols; ++col_index)
        {
            // std::cout << std::setw(8) << std::right << *(elements + row_index * m_cols + col_index) << "\t";
            std::cout << std::setw(8) << std::right << *(elements[row_index] + col_index) << "\t";
        }
        std::cout << std::endl;
    }
}

template<typename T, int N>
void Matrix<T, N>::assign(const std::vector<T>& vec)
{
    auto index = 0U;
    auto size = vec.size();
    for (int row_index = 0; row_index < N; ++row_index)
    {
        for (int col_index = 0; col_index < m_cols; ++col_index)
        {
            *(elements[row_index] + col_index) = (index >= size ? T{} : vec[index++]);
        }
    }
}

template<typename T>
void Matrix<T, 0>::showLayout()
{
    std::cout << std::setw(8) << std::right << " " << "\t"
              << std::setw(8) << std::right << "col. #1" << "\t"
              << std::endl;
    std::cout << std::setw(8) << std::left << "row. #1" << "\t" 
              << std::setw(8) << std::right << val << "\t"
              << std::endl;
}

template<typename T>
void Matrix<T, 1>::showLayout()
{
    std::cout << std::setw(8) << std::right << " " << "\t";
    for (auto col_index = 1; col_index <= sz; ++col_index)
    {
        std::cout << std::setw(8) << std::right << "col. #" << col_index << "\t";
    }
    std::cout << std::endl;
    
    std::cout << std::setw(8) << std::left << "row. #1" << "\t";
    for (auto col_index = 0; col_index < sz; ++col_index)
    {
        std::cout << std::setw(8) << std::right << elements[col_index] << "\t";
    }
    std::cout << std::endl;
}

template<typename T>
void Matrix<T, 1>::assign(const std::vector<T>& vec)
{
    auto index = 0U;
    auto size = vec.size();
    for (int col_index = 0; col_index < sz; col_index++)
    {
        elements[col_index] = (index >= size ? T{} : vec[index++]);
    }
}

template<typename T>
void Matrix<T, 2>::assign(const std::vector<T>& vec)
{
    int index = 0;
    int size = vec.size();
    for (int row_index = 0; row_index < m_row; ++row_index)
    {
        for (int col_index = 0; col_index < m_col; ++col_index)
        {
            *(elements + row_index * m_col + col_index) = ((index >= size) ? T{} : vec[index++]);
        }
    }
}

template<typename T>
void Matrix<T, 2>::showLayout()
{
    std::cout << std::setw(8) << std::right << " " << "\t";
    for (int col_index = 1; col_index <= m_col; ++col_index)
    {
        std::cout << std::setw(8) << std::right << "col. #" << col_index << "\t";
    }
    std::cout << std::endl;
    
    for (int row_index = 0; row_index < m_row; ++row_index)
    {
        std::cout << std::setw(8) << std::left << "row. #" << row_index + 1 << "\t";
        for (int col_index = 0; col_index < m_col; ++col_index)
        {
            std::cout << std::setw(8) << std::right << *(elements + row_index * m_col + col_index) << "\t";
        }
        std::cout << std::endl;
    }
}