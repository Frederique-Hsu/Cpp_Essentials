/*!
 *  \file       function_templates.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>

/*!
 *  \note   The essential use for a suffix return type comes in function template declarations \n
 *          in which the return type depends on the arguments
 */
template<class T, class U>
auto product(const std::vector<T>& x,
             const std::vector<U>& y) -> decltype(x * y);
