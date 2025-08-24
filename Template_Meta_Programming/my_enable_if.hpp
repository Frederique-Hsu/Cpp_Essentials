/*!
 *  \file       my_enable_if.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iostream>

#include "my_type_traits.hpp"

namespace my
{
    template<bool B, typename T = void>
    struct enable_if
    {
        // 默认模板，当 B 为 false 时，没有 type 成员
    };

    template<typename T>
    struct enable_if<true, T>
    {
        using type = T;     // 偏特化，当 B 为 true 时，有 type 成员
    };

    /*!
     *  \details    当 B 为 true 时，enable_if<true, T>::type 会得到 T ; 
     *              而当 B 为 false 时，enable_if<false, T>::type 会导致替换失败。 因为 enable_if<false, T> 这个模板没有 type 成员。
     *              这种替换失败不会导致编译错误，而是使得包含 enable_if 的函数重载被忽略。
     */

    template<bool B, class T = void> using enable_if_t = typename enable_if<B, T>::type;
}

template<typename T>
typename my::enable_if<my::is_integral<T>::value, void>::type printIntegralValue(T value)
{
    std::cout << "Integral value = " << value << std::endl;
}
