/*!
 *  \file       String.hpp
 *  \brief      
 *  
 */


#pragma once

#include <cstddef>
#include <iostream>

template<typename CharType>
class String
{
public:
    String();
    /* explicit */ String(const CharType*);
    String(const String&);
    String& operator=(const String&);
    ~String();
private:
    static const int short_max;
    int sz;
    CharType* ptr;
    int cap;
public:
    std::size_t size() const;
    std::size_t capacity() const;
    CharType operator[](int n);
    const CharType& operator[](int n) const;
    String& operator+=(CharType single_character);
private:
    friend std::ostream& operator<<(std::ostream& os, const String<CharType>& str)
    {
        for (auto index = 0U; index < str.sz; ++index)
        {
            os << str[index];
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, String<CharType>& str)
    {
        CharType single_character{};
        is >> single_character;
        str += single_character;
        return is;
    }
    friend bool operator<(const String<CharType>& a, const String<CharType>& b)
    {
        int len = (a.sz <= b.sz) ? a.sz : b.sz;
        
        for (int index = 0; index < len; ++index)
        {
            if (a[index] == b[index])
            {
                continue;
            }
            return a[index] < b[index];
        }
        if (a.sz < b.sz)
        {
            return true;
        }
        else    // a.sz > b.sz
        {
            return false;
        }
    }
};

namespace my
{
    using string = String<char>;
    using wstring = String<wchar_t>;
}

#if false
template<typename Container, typename ElemType>
requires Equal_comparable<Container::value_type, ElemType>
int find_index(Container& container, ElemType elem);
#endif

#include "String_impl.hpp"
