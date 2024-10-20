/*!
 *  \file       name_binding.hpp
 *  \brief      
 *  
 */


#pragma once

#include <vector>


bool tracing;

template<typename T> T sum(std::vector<T>& vec);


/*!
 *  \brief  如果被调用函数的实参或形参明显依赖于模板参数，则函数名字是依赖性名字。
 */
template<typename T> T fn(T a);

template<typename Container> void fct(Container& container);

template<typename T>
using Value_Type = typename T::value_type;

template<typename Container> void fct2(Container& container);

#include "name_binding_impl.hpp"