/*!
 *  \file       user_defined_literal_operator.hpp
 *  \brief
 *
 */


#pragma once


#include <string>
#include <stack>

std::string operator"" _s(const char* p, size_t n);

namespace Numerics
{
    class BigNum
    {
    public:
        BigNum(const char* digit_str);

    private:
        std::stack<int> m_digit_stack;

    private:
        static int digit_char_to_int(char digit_char);
        static char digit_int_to_char(int digit);

        friend std::ostream& operator<<(std::ostream& os, const BigNum& big_number);
        friend std::string operator+(const BigNum& bignum_a, const BigNum& bignum_b);
        friend std::string operator-(const BigNum& bignum_a, const BigNum& bignum_b);
        friend bool operator==(const BigNum& a, const BigNum& b);
        friend bool operator>(const BigNum& a, const BigNum& b);
    };

    namespace literals
    {
        BigNum operator"" _x(const char* p);
    }
}

/*!
 *  \section    template literal operator
 *  \details    模板字面值常量运算符 将其参数作为模板参数包，而非函数参数。
 */

constexpr int ipow(int x, int n)
{
    return (n > 0) ? x * ipow(x, n-1) : 1;
}

template<char c> constexpr int b3_helper()
{
    static_assert(c < '3', "not a ternary digit");
    return c;
}

template<char c, char... tail> constexpr int b3_helper()
{
    static_assert(c < '3', "not a ternary digit");
    return ipow(3, sizeof...(tail)) * (c - '0') + b3_helper<c, tail...>();
}

template<char... chars> constexpr int operator"" _b3()   // 3进制
{
    return b3_helper<chars...>();
}