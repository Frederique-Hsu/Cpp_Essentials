/*!
 *  \file       function_template.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>

/*!
 *  \note   后置函数返回类型的必要性源于函数模板声明，因为其返回类型是依赖于参数的。
 */
template<class T, class U>
auto product(const std::vector<T>& x, const std::vector<U>& y) -> decltype(x * y);




#include "function_template_impl.hpp"
