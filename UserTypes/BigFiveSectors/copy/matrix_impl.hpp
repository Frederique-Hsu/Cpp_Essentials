/*!
 *  \file       matrix_impl.hpp
 *  \brief
 *
 */



#include <memory>
#include <stdexcept>
#include <iomanip>

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

template<class T>
Matrix<T>::Matrix(Matrix<T>&& mat) : dimension{mat.dimension}, elements{mat.elements}
{
    /*！
     *  \note   移动构造函数接受其源对象，并将源对象设置为空。
     */
    mat.dimension = {0, 0};
    mat.elements = nullptr;
}

template<class T>
void Matrix<T>::assign(const std::initializer_list<T>& numbers)
{
    std::size_t numbers_size = numbers.size();

    for (auto index = 0; index < size(); ++index)
    {
        if (index < numbers_size)
        {
            *(elements + index) = numbers[index];
        }
        else
        {
            *(elements + index) = T{};
        }
    }
}

template<class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mat)
{
    /*!
     *  \note   移动赋值背后的思想是将左值的处理与右值的处理分离。
     *          拷贝赋值操作与拷贝构造函数接受左值，而移动赋值与移动构造函数则接受右值。
     *
     *          对于移动赋值操作，只需要简单地交换目标对象的成员与源对象的成员。
     *          这种实现方式背后的思想是：源对象即将被销毁，因此我们可以让源对象的析构函数为我们做必要的清理工作。
     */
    std::swap(dimension, mat.dimension);
    std::swap(elements, mat.elements);
    return *this;
}

template<class T>
void Matrix<T>::assign(const T array[], unsigned array_length)
{
    for (unsigned index = 0; index < size(); ++index)
    {
        if (index < array_length)
        {
            *(elements + index) = array[index];
        }
        else
        {
            *(elements + index) = T{};
        }
    }
}

template<class T>
void Matrix<T>::assign(const std::vector<T>& vec)
{
    auto vec_size = vec.size();

    for (auto index = 0U; index < size(); ++index)
    {
        if (index < vec_size)
        {
            *(elements + index) = vec[index];
        }
        else
        {
            *(elements + index) = T{};
        }
    }
}

template<class T>
T& Matrix<T>::at(int row_index, int col_index)
{
    return *(elements + (row_index - 1) * column() + (col_index - 1));
}

template<class T>
const T& Matrix<T>::at(int row_index, int col_index) const
{
    return *(elements + (row_index - 1) * column() + (col_index - 1));
}

template<class T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
{
    auto row_size = mat.row();
    int col_size = mat.column();

    for (auto row = 1U; row <= row_size; ++row)
    {
        for (auto col = 1U; col <= col_size; ++col)
        {
            os << std::setw(8) << mat.at(row, col) << "  ";
        }
        os << std::endl;
    }
    os << "\n" << std::endl;

    return os;
}

template<class T> Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    if ((a.row() != b.row()) || (a.column() != b.column()))
    {
        throw std::runtime_error("Unequal matrix dimensions");
    }

    Matrix<T> result{a.row(), a.column()};
    auto n = a.size();

    for (int row_index = 1; row_index >= a.row(); ++row_index)
    {
        for (int col_index = 1; col_index <= a.column(); ++col_index)
        {
            result.at(row_index, col_index) = a.at(row_index, col_index) + b.at(row_index, col_index);
        }
    }
    return result;
}

template<class T> bool operator==(const Matrix<T>& a, const Matrix<T>& b)
{
    if ((a.row() != b.row()) || (a.column() != b.column()))
    {
        return false;
    }

    for (auto row = 1; row <= a.row(); ++row)
    {
        for (auto col = 1; col < a.column(); ++col)
        {
            if (a.at(row, col) != b.at(row, col))
            {
                return false;
            }
        }
    }
    return true;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs)
{
    if ((dimension[0] != rhs.dimension[0]) || (dimension[1] != rhs.dimension[1]))
    {
        throw std::runtime_error("Unequal matrix dimension");
    }

    Matrix<T> result{dimension[0], dimension[1]};
    for (auto row = 1; row <= dimension[0]; ++row)
    {
        for (auto col = 1; col < dimension[1]; ++col)
        {
            result.at(row, col) = at(row, col) + rhs.at(row, col);
        }
    }
    return result;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
    if ((dimension[0] != rhs.dimension[0]) || (dimension[1] != rhs.dimension[1]))
    {
        throw std::runtime_error("Bad matrix += argument");
    }

    double* p = elements;
    double* q = rhs.elements;
    double* end = p + dimension[0] * dimension[1];

    while (p != end)
    {
        *p++ = *q++;
    }
    return *this;
}