/*!
 *  \file       generic_algorithms.cpp
 *  \brief      
 *  
 */


#include "generic_algorithms.hpp"

template<typename Iter, typename ValueType>
ValueType sum(Iter first, Iter last)
{
    ValueType sum = ValueType{};
    while (first != last)
    {
        sum += *first;
        ++first;
    }
    return sum;
}

template<typename Iter, typename ValueType> 
ValueType accumulate(Iter first, Iter last, ValueType sum)
{
    for (Iter it = first; it != last; ++it)
    {
        sum += *it;
    }
    return sum;
}

template<typename Iter, typename ValueType, typename Oper>
ValueType accumulate(Iter first, Iter last, ValueType init, Oper op)
{
    ValueType result = init;
    while (first != last)
    {
        result = op(result, *first);
        ++first;
    }
    return result;
}