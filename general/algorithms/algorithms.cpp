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

std::vector<std::string::iterator> find_all(std::string& str, char target_letter)
{
    std::vector<std::string::iterator> res;
    for (auto iter = str.begin(); iter != str.end(); ++iter)
    {
        if (*iter == target_letter)
        {
            res.push_back(iter);
        }
    }
    return res;
}
