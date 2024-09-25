/*!
 *  \file       function_template_specialization.hpp
 *  \brief      
 *  
 */


#pragma once


#include <vector>


/*!
 *  \section    Specialization and Overloading
 */

template<typename T> bool less(T a, T b);

template<> bool less<const char*>(const char* a, const char* b);

template<typename T> void sort(std::vector<T>& vec);


/*!
 *  \section    Specialization that is not overloading
 */

template<typename T> T max_value();     // no definition deliberately
template<> constexpr int max_value<int>();
template<> constexpr char max_value<char>();
template<> constexpr int* max_value<int*>();
template<> constexpr int const* max_value<int const*>();

template<typename T>
class Value_Type
{
public:
    using type = T;
};

class Dummy
{
public:
    static int max2(int)
    {
        return max_value<int>();
    }
    static char max2(char)
    {
        return max_value<char>();
    }
    static int* max2(int*)
    {
        return max_value<int*>();
    }
};

template<typename Iter> Iter my_algo(Iter p);
template<typename Iter> Iter my_algo2(Iter p);


#include "function_template_specialization_impl.hpp"