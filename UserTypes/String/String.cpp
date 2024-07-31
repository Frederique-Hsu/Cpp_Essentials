/*!
 *  \file       String.cpp
 *  \brief
 *
 */


#include "String.hpp"

#include <vector>
#include <cstring>


int hash(const String& str);

static char* expand(const char* ptr, int n)
{
    char* p = new char[n];
    std::strcpy(p, ptr);
    return p;
}

String::String() : sz{0}, ptr{ch}
{
    ch[0] = 0;
}

String::String(const char* str) : sz{std::strlen(str)},
                                  ptr{(sz <= short_max) ? ch : new char[sz+1]},
                                  space{0}
{
    std::strcpy(ptr, str);
}

String::String(const String& rhs)
{
    copy_from(rhs);
}

String::String(String&& rhs)
{
    move_from(rhs);
}

String& String::operator=(const String& rhs)
{
    if (this != &rhs)
    {
        char* p = (short_max < sz) ? ptr : 0;
        copy_from(rhs);
        delete[] p;
    }
    return *this;
}

String& String::operator=(String&& rhs)
{
    if (this != &rhs)
    {
        if (short_max < sz)
        {
            delete[] ptr;
        }
        move_from(rhs);
    }
    return *this;
}

String::~String()
{
    if (sz > short_max)
    {
        delete[] ptr;
    }
}

void String::check(int n) const
{
    if (n < 0 || n > sz)
    {
        throw std::out_of_range("String::at()");
    }
}

char& String::operator[](int n)
{
    return ptr[n];
}

char String::operator[](int n) const
{
    return ptr[n];
}

char& String::at(int n)
{
    check(n);
    return ptr[n];
}

char String::at(int n) const
{
    check(n);
    return ptr[n];
}

char* String::c_str()
{
    return ptr;
}

const char* String::c_str() const
{
    return ptr;
}

int String::size() const
{
    return sz;
}

int String::capacity() const
{
    return (sz <= short_max) ? short_max : (sz + space);
}

bool String::is_empty() const
{
    return std::strlen(ptr) == 0;
}

void String::copy_from(const String& other)
{
    if (other.sz <= short_max)
    {
        std::memcpy(this, &other, sizeof(other));
        ptr = ch;
    }
    else
    {
        ptr = expand(other.ptr, other.sz+1);
        sz = other.sz;
        space = 0;
    }
}

void String::move_from(String& other)
{
    if (other.sz <= short_max)
    {
        std::memcpy(this, &other, sizeof(other));
        ptr = ch;
    }
    else
    {
        ptr = other.ptr;
        sz = other.sz;
        space = other.space;
        other.ptr = other.ch;
        other.sz = 0;
        other.ch[0] = '\0';
    }
}

String& String::operator+=(char c)
{
    if (sz == short_max)
    {
        int n = sz + sz + 2;
        ptr = expand(ptr, n);
        space = n - sz -2;
    }
    else if (sz > short_max)
    {
        if (space == 0)
        {
            int n = sz + sz + 2;
            char* p = expand(ptr, n);
            delete[] ptr;
            ptr = p;
            space = n - sz - 2;
        }
        else
        {
            --space;
        }
    }
    ptr[sz] = c;
    ptr[++sz] = 0;

    return *this;
}

String& String::operator+=(const char* str)
{
    for (int i = 0; i < std::strlen(str); ++i)
    {
        *this += str[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    return os << str.c_str();
}

std::istream& operator>>(std::istream& is, String& str)
{
    str = String();

    is >> std::ws;  // Quick and easy to eat the whitespace
    char ch = 0;

    while (is.get(ch)/* && !std::isspace(ch) */)    // You need to press Ctrl+D to quit the entering.
    {
        str += ch;
    }
    return is;
}

bool operator==(const String& a, const String& b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int index = 0; index < a.size(); ++index)
    {
        if (a[index] != b[index])
        {
            return false;
        }
    }
    return true;
}

bool operator==(const String& a, const char* str)
{
    int len = std::strlen(str);
    if (a.size() != len)
    {
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        if (a[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

bool operator==(const char* str, const String& b)
{
    return (b == str);
}

bool operator!=(const String& a, const String& b)
{
    return !(a == b);
}

bool operator< (const String& a, const String& b)
{
    int min_len = std::min(a.size(), b.size());
    for (int index = 0; index < min_len; ++index)
    {
        if (a.at(index) >= b.at(index))
        {
            return false;
        }
    }
    if (a.size() > b.size())
    {
        return false;
    }
    return true;
}

bool operator<=(const String& a, const String& b)
{
    int min_len = std::min(a.size(), b.size());
    for (int index = 0; index < min_len; ++index)
    {
        if (a.at(index) > b.at(index))
        {
            return false;
        }
    }
    if (a.size() > b.size())
    {
        return false;
    }
    return true;
}

bool operator> (const String& a, const String& b)
{
    return !(b <= a);
}

bool operator>=(const String& a, const String& b)
{
    return !(b < a);
}

char* begin(String& str)
{
    return str.c_str();
}

char* end(String& str)
{
    return str.c_str() + str.size();
}

const char* begin(const String& str)
{
    return str.c_str();
}

const char* end(const String& str)
{
    return str.c_str() + str.size();
}

String& operator+=(String& a, const String& b)
{
    for (auto elem : b)
    {
        a += elem;
    }
    return a;
}

String  operator+(const String& a, const String& b)
{
    String result(a);
    result += b;
    return result;
}

String operator"" _s(const char* str, std::size_t)
{
    return String(str);
}

int hash(const String& str)
{
    int h{str[0]};
    for (int i{1}; i != str.size(); ++i)
    {
        h ^= str[i] >> 1;
    }
    return h;
}

static void print_in_order(const String& str, const std::vector<int>& indices)
{
    for (auto index : indices)
    {
        std::cout << str.at(index) << std::endl;
    }
}