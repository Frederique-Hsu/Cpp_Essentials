/*!
 *  \file       Lists.cpp
 *  \brief
 *
 */


#include "Lists.hpp"

#include <ext/numeric_traits.h>
#include <boost/detail/numeric_traits.hpp>
#include <limits>


void f(S)
{
}

void g(S)
{
}

void g(SS)
{
}

void h()
{
    f({1, 2});      // OK: 调用f(S{1, 2})

    // g({1, 2});      // Error: 存在歧义
    g(S{1, 2});     // OK: 调用g(S)
    g(SS{1, 2});    // OK: 调用g(SS)

    /*!
     *  \note   当我们用列表初始化命名变量时，列表中可以包含0个，1个或者多个元素。
     *          {}列表构建的是某种类型的对象，因此其中包含的元素数量和类型都必须符合构建该类型对象的要求。
     */
}

/*!
 *  \brief  使用标准库类型initializer_list<T>用于处理长度可变的{}列表
 */
int high_value(std::initializer_list<int> values)
{
    int high = std::numeric_limits<int>::lowest();
    if (values.size() == 0)
    {
        return high;
    }

    for (auto value : values)
    {
        if (value > high)
        {
            high = value;
        }
    }
    return high;
}
