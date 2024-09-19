/*!
 *  \file       String_impl.hpp
 *  \brief      
 *  
 */


#include <stdexcept>
#include <memory>
#include <cstring>
#include <cwchar>
#include <cstdlib>

template<typename CharType>
const int String<CharType>::short_max = 15;

template<typename CharType>
String<CharType>::String() : sz{0}, ptr{nullptr}, cap{short_max}
{
    ptr = new CharType[short_max];
    if (ptr == nullptr)
    {
        throw std::bad_alloc();
    }
    // ptr[short_max] = '\0';
    
    std::uninitialized_fill(ptr, ptr+short_max, CharType{});
}

template<typename CharType>
String<CharType>::~String()
{
    if (ptr != nullptr)
    {
        delete [] ptr;
    }
}

template<typename CharType>
String<CharType>::String(const String<CharType>& rhs) : sz{rhs.sz}, ptr{nullptr}, cap{rhs.cap}
{
    ptr = new CharType[cap];
    if (ptr == nullptr)
    {
        throw std::bad_alloc();
    }
    std::memset(ptr, 0, sizeof(CharType) * cap);
    for (int index = 0; index < sz; ++index)
    {
        *(ptr+index) = rhs[index];
    }
}

template<typename CharType>
inline CharType String<CharType>::operator[](int n)     /*! \attention  可以将inline加到类外来实现的成员函数前，也可以告诉编译器将此成员函数编译成内联，不需要采取函数调用方式。 */
{
    return *(ptr + n);
}

template<typename CharType>
inline const CharType& String<CharType>::operator[](int n) const
{
    return *(ptr + n);
}

template<typename CharType>
std::size_t String<CharType>::size() const
{
    return sz;
}

template<typename CharType>
std::size_t String<CharType>::capacity() const
{
    return cap;
}

template<typename CharType>
String<CharType>::String(const CharType* str) : sz{0}, ptr{nullptr}, cap{0}
{
    #if true
    std::size_t len = std::strlen(str);
    #else
    if (typeid(str).name() == typeid(wchar_t).name())
    {
        len = std::wcslen(str);
    }
    #endif
    
    sz = (len <= short_max) ? short_max : len;
    cap = sz * 2;
    ptr = new CharType[cap];
    if (ptr == nullptr)
    {
        throw std::bad_alloc();
    }
    std::memset(ptr, 0, sizeof(CharType) * cap);
    
    for (auto index = 0U; index < len; ++index)
    {
        *(ptr + index) = *(str + index);
    }
}

template<typename CharType>
String<CharType>& String<CharType>::operator+=(CharType single_character)
{
    if ((sz + 1) < cap)
    {
        *(ptr + sz) = single_character;
        sz++;
        return *this;
    }
    else    // sz >= cap
    {
        cap += (2 * sz);
        ptr = (CharType*)std::realloc(ptr, sizeof(CharType) * cap);
        if (ptr == nullptr)
        {
            throw std::bad_alloc();
        }
        *(ptr + sz) = single_character;
        sz++;
        return *this;
    }
}

#if false
template<typename CharType>
std::ostream& operator<<(std::ostream& os, const String<CharType>& str)
{
    for (auto index = 0U; index < str.sz; ++index)
    {
        os << str[index];
    }
    return os;
}

template<typename CharType>
std::istream& operator>>(std::istream& is, String<CharType>& str)
{
    CharType single_character{};
    is >> single_character;
    str += single_character;
    return is;
}

template<typename CharType>
bool operator<(const String<CharType>& a, const String<CharType>& b)
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
#endif

template<typename CharType>
String<CharType>& String<CharType>::operator=(const String<CharType>& rhs)
{
    if (this != &rhs)
    {
        sz = rhs.sz;
        cap = rhs.cap;
        ptr = new CharType[cap];
        if (ptr == nullptr)
        {
            throw std::bad_alloc();
        }
        std::memset(ptr, 0, sizeof(CharType) * cap);
        for (int index = 0; index < sz; ++index)
        {
            *(ptr + index) = rhs[index];
        }
    }
    return *this;
}