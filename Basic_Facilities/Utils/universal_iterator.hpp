/*!
 *  \file       universal_iterator.hpp
 *  \brief      Study the iterator_traits technique.
 *
 */


#pragma once

#include <iterator>
#include <algorithm>

/* Declaration ===================================================================================*/
template<typename Ran>
void sort_helper(Ran begin, Ran end, std::random_access_iterator_tag);

template<typename For>
void sort_helper(For begin, For end, std::forward_iterator_tag);

template<typename Container>
void sort(Container& container);

template<typename Container> using Iterator_type = typename Container::iterator;

template<typename Iter> using Iterator_category = typename std::iterator_traits<Iter>::iterator_category;


/* Implementation ================================================================================*/
template<typename Ran>
void sort_helper(Ran begin, Ran end, std::random_access_iterator_tag)
{
    std::sort(begin, end);
}

template<typename For>
void sort_helper(For begin, For end, std::forward_iterator_tag)
{
    std::vector<decltype(*begin)> vec(begin, end);
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), begin);
}

template<typename Container>
void sort(Container& container)
{
    using Iter = Iterator_type<Container>;
    sort_helper(container.begin(), container.end(), Iterator_category<Iter>{});
}
