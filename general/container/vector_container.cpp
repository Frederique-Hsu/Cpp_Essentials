/*!
 *  \file       vector_container.cpp
 *  \brief
 *
 */


#include "vector_container.hpp"

std::ostream& operator<<(std::ostream& os, const Entry& entry)
{
    return os << "{\"" << entry.name << "\", " << entry.number << "}";
}

void print_book(const std::vector<Entry>& book)
{
#if 0
    for (std::size_t index = 0; index != book.size(); ++index)
    {
        std::cout << book[index] << "\n";
    }
#else
    for (const auto& elem : book)
    {
        std::cout << elem << std::endl;
    }
#endif
}
