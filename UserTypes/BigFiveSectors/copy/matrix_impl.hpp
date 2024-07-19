/*!
 *  \file       matrix_impl.hpp
 *  \brief
 *
 */



#include <memory>
#include <stdexcept>

template<class T>
Matrix<T>::Matrix(int row, int column) : dimension{row, column}, elements{new T[row * column]}
{
}

template<class T>
Matrix<T>::~Matrix()
{
    if (elements != nullptr)
    {
        delete [] elements;
    }
}

template<class T>
int Matrix<T>::size() const
{
    return dimension[0] * dimension[1];
}

template<class T>
int Matrix<T>::row() const
{
    return dimension[0];
}

template<class T>
int Matrix<T>::column() const
{
    return dimension[1];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& mat) : dimension{mat.dimension}, elements{new T[mat.size()]}
{
    std::uninitialized_copy(mat.elements, mat.elements + mat.size(), elements);
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat)
{
#if false
    if (this != &mat)
    {
        if ((dimension[0] != mat.dimension[0]) or (dimension[1] != mat.dimension[1]))
        {
            throw std::runtime_error("The dimension does not match between the 2 matrices");
        }
        std::copy(mat.elements, mat.elements + mat.size(), elements);
    }
#else
    Matrix<T> tmp{mat};
    std::swap(tmp, *this);
#endif
    return *this;
}
