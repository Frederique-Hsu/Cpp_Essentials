/*!
 *  \file       carry_counting_system.cpp
 *  \brief
 *
 */


#include "carry_counting_system.hpp"

#include <cstring>
#include <string>

namespace carry_counting_system
{
Binary operator"" _b(const char* bin_str)
{
    return Binary(bin_str);
}

Binary operator"" _B(const char* bin_str)
{
    return Binary(bin_str);
}

Hexadecimal operator"" _h(const char* hex_str)
{
    return Hexadecimal(hex_str);
}

Hexadecimal operator"" _H(const char* hex_str)
{
    return Hexadecimal(hex_str);
}

/*================================================================================================*/

int Binary::bin_char_to_int(char bin_char)
{
    switch (bin_char)
    {
    case '0':   return 0;
    case '1':   return 1;
    default:
        throw std::invalid_argument("The bin_char is not binary format.");
        break;
    }
}

char Binary::int_to_bin_char(int digit)
{
    switch (digit)
    {
    case 0:     return '0';
    case 1:     return '1';
    default:
        throw std::invalid_argument("The digit is not binary format.");
        break;
    }
}

Binary::Binary(const char* bin_str) : m_stack{}
{
    std::size_t length = std::strlen(bin_str);

    bool is_first_non_zero = false;
    for (auto i = 0U; i < length; ++i)
    {
        if ((bin_str[i] == '0') && (is_first_non_zero == false))
        {
            is_first_non_zero = true;
        }
        else
        {
            m_stack.push(bin_char_to_int(bin_str[i]));
            is_first_non_zero = true;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Binary& bin)
{
    std::stack<int> bin_stack = bin.m_stack;
    std::string bin_str;

    int index = 1;
    auto size = bin_stack.size();
    while (!bin_stack.empty())
    {
        bin_str.insert(0, 1, Binary::int_to_bin_char(bin_stack.top()));
        if ((index % 4 == 0) && (index != size))
        {
            bin_str.insert(0, 1, ',');
        }
        index++;

        bin_stack.pop();
    }
    os << bin_str;
    return os;
}

bool operator==(const Binary& a, const Binary& b)
{
    std::stack<int> stack_a = a.m_stack;
    std::stack<int> stack_b = b.m_stack;

    if (stack_a.size() != stack_b.size())
    {
        return false;
    }
    while (!stack_a.empty())
    {
        int num_a = stack_a.top();
        int num_b = stack_b.top();

        if (num_a != num_b)
        {
            return false;
        }
        stack_a.pop();
        stack_b.pop();
    }
    return true;
}

int Hexadecimal::hex_char_to_int(char hex_char)
{
    switch (hex_char)
    {
    case '0':   return 0;
    case '1':   return 1;
    case '2':   return 2;
    case '3':   return 3;
    case '4':   return 4;
    case '5':   return 5;
    case '6':   return 6;
    case '7':   return 7;
    case '8':   return 8;
    case '9':   return 9;
    case 'a':
    case 'A':   return 10;
    case 'b':
    case 'B':   return 11;
    case 'c':
    case 'C':   return 12;
    case 'd':
    case 'D':   return 13;
    case 'e':
    case 'E':   return 14;
    case 'f':
    case 'F':   return 15;
    default:
        throw std::invalid_argument("The hex_char is not hexedecimal format.");
        break;
    }
}

char Hexadecimal::int_to_hex_char(int digit)
{
    switch (digit)
    {
    case 0:     return '0';
    case 1:     return '1';
    case 2:     return '2';
    case 3:     return '3';
    case 4:     return '4';
    case 5:     return '5';
    case 6:     return '6';
    case 7:     return '7';
    case 8:     return '8';
    case 9:     return '9';
    case 10:    return 'A';
    case 11:    return 'B';
    case 12:    return 'C';
    case 13:    return 'D';
    case 14:    return 'E';
    case 15:    return 'F';
    default:
        throw std::invalid_argument("The digit is not the hex format.");
        break;
    }
}

Hexadecimal::Hexadecimal(const char* hex_str)
{
    int len = std::strlen(hex_str);

    bool is_first_non_zero = false;
    for (int i = 0; i < len; ++i)
    {
        char hex_char = hex_str[i];
        if ((hex_char == '0') && (is_first_non_zero == false))
        {
            is_first_non_zero = true;
        }
        else
        {
            m_stack.push(hex_char_to_int(hex_char));
            is_first_non_zero = true;
        }
    }
}

Binary Hexadecimal::ToBin() const
{
    std::stack<int> hex_stack = m_stack;

    std::string bin_str;
    while (!hex_stack.empty())
    {
        char* bin_char = int_to_bin_str(hex_stack.top());
        bin_str.insert(0, bin_char, 4);

        hex_stack.pop();
    }

    return Binary(bin_str.c_str());
}

char* Hexadecimal::int_to_bin_str(int num) const
{
    switch (num)
    {
    case 0:     return (char*)("0000");
    case 1:     return (char*)("0001");
    case 2:     return (char*)("0010");
    case 3:     return (char*)("0011");
    case 4:     return (char*)("0100");
    case 5:     return (char*)("0101");
    case 6:     return (char*)("0110");
    case 7:     return (char*)("0111");
    case 8:     return (char*)("1000");
    case 9:     return (char*)("1001");
    case 10:    return (char*)("1010");
    case 11:    return (char*)("1011");
    case 12:    return (char*)("1100");
    case 13:    return (char*)("1101");
    case 14:    return (char*)("1110");
    case 15:    return (char*)("1111");
    default:
        throw std::invalid_argument("The num is not hex format.");
        break;
    }
}

std::ostream& operator<<(std::ostream& os, const Hexadecimal& hex)
{
    std::string hex_str;

    std::stack<int> hex_stack = hex.m_stack;
    auto size = hex_stack.size();

    int index = 1;
    while (!hex_stack.empty())
    {
        char hex_char = Hexadecimal::int_to_hex_char(hex_stack.top());
        hex_str.insert(0, 1, hex_char);
        if ((index % 4 == 0) && (index != size))
        {
            hex_str.insert(0, 1, ',');
        }
        index++;

        hex_stack.pop();
    }
    hex_str.insert(0, "0x", 2);

    os << hex_str;
    return os;
}
}