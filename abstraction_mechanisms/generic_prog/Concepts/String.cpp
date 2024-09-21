/*!
 *  \file       String.cpp
 *  \brief      
 *  
 */


#include "String.hpp"

static_assert(std::totally_ordered<std::string>, "std::string is not totally ordered");


template<typename TChar>
std::size_t String<TChar>::size() const
{
    return m_size;
}

template<typename TChar>
bool operator==(const String<TChar>& a, const String<TChar>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (auto index = 0U; index != a.size(); ++index)
    {
        if (a[index] != b[index])
        {
            return false;
        }
    }
    return true;
}

template<typename TChar>
bool operator!=(const String<TChar>& lhs, const String<TChar>& rhs)
{
    return !(lhs == rhs);
}

template<typename TChar>
bool operator<(const String<TChar>& a, const String<TChar>& b)
{    
    bool equal = true;
    for (auto index = 0U; index != a.size() && index != b.size(); ++index)
    {
        if (b[index] < a[index])
            return false;
        if (a[index] < b[index])
        {
            equal = false;
        }
    }
    if (b.size() < a.size())
    {
        return false;
    }
    if (a.size() == b.size() && equal)
    {
        return false;
    }
    return true;
}

template<typename TChar> 
std::ostream& operator<<(std::ostream& os, const String<TChar>& str)
{    
    for (auto index = 0U; index!= str.size(); ++index)
    {
        os << str[index];
    }
    return os;
}