/*!
 *  \file       carry_counting_system.hpp
 *  \brief
 *
 */


#pragma once


#include <stack>
#include <iostream>

namespace carry_counting_system
{
class Binary;
class Octal;
class Hexadecimal;
class Decimal;

Binary operator"" _b(const char* bin_str);
Binary operator"" _B(const char* bin_str);

Octal operator"" _o(const char* oct_str);
// Octal operator"" _O(const char* oct_str);

Hexadecimal operator"" _h(const char* hex_str);
Hexadecimal operator"" _H(const char* hex_str);



class Binary
{
    friend std::ostream& operator<<(std::ostream& os, const Binary& bin);
    friend bool operator==(const Binary& a, const Binary& b);
public:
    Binary(const char* bin_str);

private:
    std::stack<int> m_stack;

public:
    Hexadecimal ToHex() const;
    Decimal ToDec() const;
    Octal ToOct() const;

    static int  bin_char_to_int(char bin_char);
    static char int_to_bin_char(int digit);
};

class Octal
{
public:
    Octal(const char* oct_str);

private:
    std::stack<int> m_stack;

public:
    Hexadecimal ToHex() const;
    Decimal ToDec() const;
    Binary ToBin() const;

    static int  oct_char_to_int(char oct_char);
    static char int_to_oct_char(int digit);
};

class Hexadecimal
{
    friend std::ostream& operator<<(std::ostream& os, const Hexadecimal& hex);
public:
    Hexadecimal(const char* hex_str);

private:
    std::stack<int> m_stack;

public:
    Decimal ToDec() const;
    Binary ToBin() const;
    Octal ToOct() const;

    static int  hex_char_to_int(char hex_char);
    static char int_to_hex_char(int digit);

private:
    char* int_to_bin_str(int num) const;
};
}