/*!
 *  \file       user_defined_algorithms.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>

/* Declaration ===================================================================================*/
template<typename T> using Iterator = typename T::iterator;

template<typename Container, typename Value>
std::vector<Iterator<Container>> find_all_elements_from_container(Container& container, Value value);


/* Implementation ================================================================================*/
template<typename Container, typename Value>
std::vector<Iterator<Container>> find_all_elements_from_container(Container& container, Value value)
{
    std::vector<Iterator<Container>> res;
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        if (*iter == value)
        {
            res.push_back(iter);
        }
    }
    return res;
}
