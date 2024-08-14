/*!
 *  \file       type_deduction.hpp
 *  \brief      研究C++的类型推断： auto和decltype()
 *
 */



#pragma once

void type_deducing(int& v)
{
    auto x = v;     // x的类型是int, 而不是int&
    auto& y = v;    // y的类型是int&
}

long getCppStandardNo()
{
    return __cplusplus;
}

template<typename ElemType> class Matrix;

/*!
 *  \brief      矩阵加法
 *  \details    如果我们想编写一个函数令其执行两个矩阵的加法运算，但是两个矩阵的元素类型可能不同，
 *              那么相加之后所得结果得类型应该是什么呢？ 当然是矩阵。
 *              但是这个结果矩阵的元素是什么类型？最自然的回答是：结果矩阵的元素类型应该是对应元素
 *              求和后的类型。
 */
template<class T, class U>
auto operator+(const Matrix<T>& a, const Matrix<U>& b) -> Matrix<decltype(T{} + U{})>;

template<class T, class U>
auto operator+(const Matrix<T>& a, const Matrix<U>& b) -> Matrix<decltype(T{} + U{})>
{
    Matrix<decltype(T{} + U{})> res;
    for (int i = 0; i != a.rows(); ++i)
    {
        for (int j = 0; j != a.cols(); ++j)
        {
            res(i, j) += a(i, j) + b(i, j);
        }
    }
    return res;
}
