/*!
 *  \file       matrix.hpp
 *  \brief
 *
 */


#pragma once

#include <array>
#include <iostream>
#include <vector>


template<class T> class Matrix
{
public:
    Matrix(int row, int column);
    Matrix(const Matrix<T>& mat);
    Matrix(Matrix<T>&& rhs);
    Matrix& operator=(const Matrix<T>& mat);
    Matrix& operator=(Matrix<T>&&);
    ~Matrix();

private:
    std::array<int, 2> dimension;
    T* elements;

public:
    int size() const;
    int row() const;
    int column() const;
    void assign(const std::initializer_list<T>& numbers);
    void assign(const T array[], unsigned array_length);
    void assign(const std::vector<T>& vec);
    T& at(int row_index = 1, int col_index = 1);
    const T& at(int row_index = 1, int col_index = 1) const;

    Matrix<T> operator+(const Matrix<T>& rhs);
    Matrix<T>& operator+=(const Matrix<T>& rhs);
};

template<class T> Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b);
template<class T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat);
template<class T> bool operator==(const Matrix<T>& a, const Matrix<T>& b);


#include "matrix_impl.hpp"