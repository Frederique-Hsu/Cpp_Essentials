/*!
 *  \file       String.hpp
 *  \brief      
 *  
 */


#pragma once

#include <cstddef>
#include <iostream>

template<typename TChar = char>
class String
{
public:
    String();
    String(const TChar* str);
    String(const String& rhs);
    String& operator=(const String& rhs);
    ~String();
private:
    TChar* m_str;
    std::size_t m_size;
public:
    std::size_t size() const;
};

template<typename TChar>
bool operator==(const String<TChar>& a, const String<TChar>& b);

template<typename TChar>
bool operator!=(const String<TChar>& lhs, const String<TChar>& rhs);

template<typename TChar>
bool operator<(const String<TChar>& a, const String<TChar>& b);

template<typename T> constexpr bool Streamable();
template<typename TChar> std::ostream& operator<<(std::ostream& os, const String<TChar>& str);
template<typename TChar> std::istream& operator>>(std::istream& is,       String<TChar>& str);

using string = String<char>;
int       stoi (const string& str, std::size_t* pos = nullptr, int base = 10);
long      stol (const string& str, std::size_t* pos = nullptr, int base = 10);
long long stoll(const string& str, std::size_t* pos = nullptr, int base = 10);

using wstring = String<wchar_t>;

enum class RSP
{
    kRock,
    kScissors,
    kPaper,
    kShoot
};