/*!
 *  \file       algorithms.cpp
 *  \brief
 *
 */


#include "algorithms.hpp"

#include <algorithm>

void unique_sort_copy(std::vector<Entry>& vec, std::list<Entry>& lst)
{
    std::sort(vec.begin(), vec.end());
    std::unique_copy(vec.begin(), vec.end(), lst.begin());
}

std::list<Entry> unique_sort_append(std::vector<Entry>& vec)
{
    std::list<Entry> res;
    std::sort(vec.begin(), vec.end());
    std::unique_copy(vec.begin(), vec.end(), std::back_inserter(res));
    return res;
}
