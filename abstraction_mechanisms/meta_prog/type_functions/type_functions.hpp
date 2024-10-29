/*!
 *  \file       type_functions.hpp
 *  \brief
 *
 */


#pragma once

#include "../control_structures/select.hpp"

/*!
 *  \section    Type function 类型函数
 *
 *  \brief      类型函数是编译时函数。即：类型函数只接受在编译时已知的参数（类型或值），
 *              并生成编译时可用的结果（类型或值）。
 */
template<typename T, int N>
struct ArrayType
{
    using type = T;
    static const int dim = N;
};

using Array3D = ArrayType<int, 3>;


template<int N>
struct Integer
{
    using Error = void;
    using type = estd::Select<N, Error,  signed char,    short,
                                 Error,  int,            Error*,
                                 Error,  Error,          long>;
};