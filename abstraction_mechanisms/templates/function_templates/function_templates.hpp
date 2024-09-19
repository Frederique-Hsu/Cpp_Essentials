/*!
 *  \file       function_templates.hpp
 *  \brief      
 *  
 */


#pragma once


#include <vector>
#include <string>
#include <utility>

template<typename T> void sort(std::vector<T>&);

template<typename T, typename Comparator = std::less<T>> void shell_sort(std::vector<T>&);

struct NoCaseComparator
{
    bool operator()(const std::string& a, const std::string& b);
};

template<typename T1, typename T2> std::pair<T1, T2> make_pair(T1 a, T2 b);


#include "function_templates_impl.hpp"