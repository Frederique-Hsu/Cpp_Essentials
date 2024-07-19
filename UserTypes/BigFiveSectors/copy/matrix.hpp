/*!
 *  \file       matrix.hpp
 *  \brief
 *
 */


#pragma once

#include <array>

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
};

#include "matrix_impl.hpp"


