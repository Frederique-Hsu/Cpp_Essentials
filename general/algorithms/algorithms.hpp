/*!
 *  \file       algorithms.hpp
 *  \brief
 *
 */


#pragma once

#include "phone_book.hpp"

#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>

void unique_sort_copy(std::vector<Entry>& vec, std::list<Entry>& lst);
std::list<Entry> unique_sort_append(std::vector<Entry>& vec);
std::vector<std::string::iterator> find_all(std::string& str, char target_letter);


/* Template declaration ==========================================================================*/
template<typename Container, typename Value>
std::vector<typename Container::iterator> find_all(Container& container, Value value);

namespace estd
{
    template<class Container> void sort(Container& container)
    {
        std::sort(container.begin(), container.end());
    }
    template<class Container, class Predicate> void sort(Container& container, Predicate condition)
    {
        std::sort(container.begin(). container.end(), condition);
    }
}


/* Template implementation =======================================================================*/
template<typename Container, typename Value>
std::vector<typename Container::iterator> find_all(Container& container, Value value)
{
    std::vector<typename Container::iterator> res;
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        if (*iter == value)
            res.push_back(iter);
    }
    return res;
}
