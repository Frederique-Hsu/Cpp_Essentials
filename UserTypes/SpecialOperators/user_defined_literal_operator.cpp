/*!
 *  \file       user_defined_literal_operator.cpp
 *  \brief
 *
 */


#include "user_defined_literal_operator.hpp"

#include <cstring>
#include <stdexcept>
#include <list>

std::string operator"" _s(const char* p, size_t n)
{
    return std::string{p, n};
}

namespace Numerics
{
    int BigNum::digit_char_to_int(char digit_char)
    {
        switch (digit_char)
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
        default:
            throw std::invalid_argument("The character is not a digit.");
            break;
        }
    }

    char BigNum::digit_int_to_char(int digit)
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
        default:
            throw std::invalid_argument("The argument is not a digit.");
            break;
        }
    }

    BigNum::BigNum(const char* digit_str) : m_digit_stack{}
    {
        bool is_first_non_zero = false;

        for (int i = 0; i < std::strlen(digit_str); ++i)
        {
            char digit_char = digit_str[i];
            if ((digit_char == '0') && (is_first_non_zero == false))
            {
                is_first_non_zero = true;
            }
            else
            {
                int digit = digit_char_to_int(digit_char);
                m_digit_stack.push(digit);

                is_first_non_zero = true;
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const BigNum& big_number)
    {
        std::stack<int> big_num_stack = big_number.m_digit_stack;
        std::string str;

        int index = 1;
        auto size = big_num_stack.size();
        while (!big_num_stack.empty())
        {
            char digit = BigNum::digit_int_to_char(big_num_stack.top());
            str.insert(0, 1, digit);

            if ((index % 4 == 0) && (index != size))
            {
                str.insert(0, 1, ',');
            }
            index++;

            big_num_stack.pop();
        }
        os << str;
        return os;
    }

    std::string operator+(const BigNum& bignum_a, const BigNum& bignum_b)
    {
        std::stack<int> stack_a = bignum_a.m_digit_stack;
        std::stack<int> stack_b = bignum_b.m_digit_stack;

        std::list<int> result(0);

        int quotient = 0;
        while (!stack_a.empty() or !stack_b.empty())
        {
            int numa = stack_a.empty() == true ? 0 : stack_a.top();
            int numb = stack_b.empty() == true ? 0 : stack_b.top();

            int remainder = (numa + numb + quotient) % 10;
            quotient = (numa + numb + quotient) / 10;

            result.push_front(remainder);

            if (!stack_a.empty())
                stack_a.pop();
            if (!stack_b.empty())
                stack_b.pop();
        }
        if (quotient > 0)
        {
            result.push_front(quotient);
        }

        std::string sumstr;
        for (int& digit : result)
        {
            char digit_char = BigNum::digit_int_to_char(digit);
            sumstr.push_back(digit_char);
        }
        return sumstr;
    }

    bool operator==(const BigNum& a, const BigNum& b)
    {
        if (a.m_digit_stack.size() != b.m_digit_stack.size())
        {
            return false;
        }

        std::stack<int> stack_a = a.m_digit_stack;
        std::stack<int> stack_b = b.m_digit_stack;
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

    namespace literals
    {
        BigNum operator"" _x(const char* p)
        {
            return BigNum(p);
        }
    }
}