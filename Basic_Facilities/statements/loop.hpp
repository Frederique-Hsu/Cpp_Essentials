/*!
 *  \file       loop.hpp
 *  \brief
 *
 */



#pragma once

#include <vector>


/* Declaration ===================================================================================*/
template<class T> T accum(std::vector<T>& vec);
template<class Iter, class Value> Iter find(Iter first, Iter last, Value val);

void input();
void print_backwards(char a[], int i);


/* Implementation ================================================================================*/
template<class T> T accum(std::vector<T>& vec)
{
    T sum = 0;
    for (const T& elem : vec)
    {
        sum += elem;
    }
    return sum;
}

template<class Iter, class Value> Iter find(Iter first, Iter last, Value val)
{
    while (first != last && *first != val)
    {
        ++first;
    }
    return first;
}
