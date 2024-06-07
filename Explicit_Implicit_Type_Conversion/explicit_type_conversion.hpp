/*!
 *  \file       explicit_type_conversion.hpp
 *  \brife
 *
 */


#pragma once

#include <stdexcept>
#include <iostream>

/*!
 *  \section    Prototypes
 */
template<class Target, class Source> Target narrow_cast(Source v);


/*!
 *  \section    Implementations
 */
template<class Target, class Source>
Target narrow_cast(Source val)
{
    /*!
     *  \note   对于发生在两种标量数字类型之间的转换，可以使用一种自制的显式类型转换函数 narrow_cast
     */
    Target ret = static_cast<Target>(val);  // 先将值转化成目标类型
    if (static_cast<Source>(ret) != val)    // 再反转回来，与原值进行比较，看能不能还原回来。
    {
        // 如果还原不回来，说明发生了窄化，就抛出异常。
        throw std::runtime_error("narrow_cast<>() failed!");
    }
    return ret;
}

template<class T> void fn(const T& t)
{
    std::cout << t << std::endl;
}
