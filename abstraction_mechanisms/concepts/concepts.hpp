/*!
 *  \file       concepts.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
concept Incrementable = std::is_integral<T>::value || std::is_enum<T>::value;

template<typename Container>
concept HasSizeMember = requires(Container c)
{
    { c.size() } -> std::same_as<std::size_t>;
};

template<typename T>
concept Printable = requires(T t)
{
    std::cout << t;
};

template<typename T>
concept IncrementableAndPrintable = Incrementable<T> && Printable<T>;


template<IncrementableAndPrintable T, HasSizeMember Container>
void print_and_increment(T& value, Container& container);


/*================================================================================================*/


template<IncrementableAndPrintable T, HasSizeMember Container>
void print_and_increment(T& value, Container& container)
{
    std::cout << "Container size: " << container.size() << std::endl;
    std::cout << "value before increment: " << value << std::endl;

    ++value;
    std::cout << "value after increment: " << value << std::endl;
}

/*================================================================================================*/

template<typename Iterator>
struct iterator_traits
{
    using value_type = typename Iterator::value_type;
};

template<typename T>
struct iterator_traits<T*>
{
    using value_type = T;
};

template<typename Iterator>
using value_type_t = typename iterator_traits<Iterator>::value_type;

template<std::input_iterator InIter,
         std::sentinel_for<InIter> SentIter,
         std::output_iterator<value_type_t<InIter>> OutIter>
    requires std::indirectly_copyable<InIter, OutIter>
OutIter user_copy(InIter first, SentIter last, OutIter result)
{
    std::cout << "called user_copy(InIter first, InIter last, OutIter result)" << std::endl;
    return std::copy(first, last, result);
}