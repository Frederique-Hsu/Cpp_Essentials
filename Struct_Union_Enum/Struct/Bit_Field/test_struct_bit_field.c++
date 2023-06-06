/*!
 *  \file       test_struct_bit_filed.c++
 *  \brief      
 *  
 */


#include "struct_bit_field.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <cstdint>
#include <bit>

TEST(UTester4StructBitField, AssignBitField)
{
    S obj = {6};

    ++obj.b;    // store the value 7 in the bit-field.
    std::cout << obj.b << std::endl;

    ++obj.b;    // the value 8 does not fit in this bit-field.
    std::cout << obj.b << std::endl;
}


TEST(UTester4StructBitField, AccessAdjacentBitFields)
{
    std::cout << "sizeof(AddressBit) = " << sizeof(AddressBit) << std::endl;

    AddressBit addr;
    addr.b1 = 0b111;
    addr.b2 = 0b10'1011;
    addr.b3 = 0b11;

#if (__cplusplus >= 202002L)
    auto bits = std::bit_cast<std::uint16_t>(addr);
#else
    auto bits = bit_cast<std::uint16_t>(addr);
#endif
    std::cout << bits << std::endl;

    std::cout << "0b";
    for (std::uint16_t b = bits, count = 1; b; b >>= 1, ++count)
    {
        std::cout << (b & 1);
        if (count % 4 == 0)
        {
            std::cout << "'";
        }
    }
    std:: cout << "\n" << std::endl;
}