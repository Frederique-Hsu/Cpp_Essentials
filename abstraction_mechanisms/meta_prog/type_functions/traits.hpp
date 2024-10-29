/*!
 *  \file       traits.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iterator>

/*!
 *  \section    萃取 trait 技术被用来关联属性与类型
 *              你可以将萃取理解为返回很多结果的类型函数或者一组类型函数
 */

template<typename Iterator>
struct iterator_traits
{
    using difference_type = typename Iterator::difference_type;
    using value_type = typename Iterator::value_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
    using iterator_category = typename Iterator::iterator_category;
};

template<typename Iter>
Iter Search(Iter p, Iter q, typename iterator_traits<Iter>::value_type target)
{
    typename iterator_traits<Iter>::difference_type distance = q - p;

    for (Iter it = p; it != q; ++it)
    {
        typename iterator_traits<Iter>::value_type value = *it;
        if (value == target)
        {
            return it;
        }
    }
    return Iter();
}

template<typename T>
using Value_Type = typename std::iterator_traits<T>::value_type;

template<typename T>
using Difference_Type = typename std::iterator_traits<T>::difference_type;

template<typename T>
using iterator_category = typename std::iterator_traits<T>::iterator_category;

template<typename Iter>
Iter Binary_Search(Iter p, Iter q, Value_Type<Iter> val)
{
    Iter low = p, high = q;
    auto difference = high - low;
    Iter mid = low + difference / 2;

    while (low <= high)
    {
        if (*mid < val)
        {
            low = mid + 1;
        }
        else if (*mid > val)
        {
            high = mid - 1;
        }
        else if (*mid == val)
        {
            return mid;
        }
        difference = high - low;
        mid = low + difference / 2;
    }
    return Iter();
}