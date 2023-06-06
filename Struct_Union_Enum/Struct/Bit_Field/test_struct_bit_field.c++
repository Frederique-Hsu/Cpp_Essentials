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
#include <stdio.h>

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
}

TEST(UTester4StructBitField, CheckSpecificBitFieldWith0Size)
{
    std::cout << "sizeof(SpecificBitField) = " << sizeof(SpecificBitField) << std::endl;
}

/*================================================================================================*/

int a;
const int b = 5;

struct BitField
{
    int x1 : 8 = 42;                // OK: "=42" is brace-or-equal-initializer
    int x2 : 8 {42};                // OK: "{42}" is brace-or-equal-initializer

    int y1 : true ? 8 : a = 42;     // OK: brace-or-equal-initializer is absent
    // int y2 : true ? 8 : b = 42;     // Error: cannot assign to const int.
    int y3 : (false ? 8 : b) = 42;   // OK: "= 42" is brace-or-equal-initializer
    int z  : 1 || new int{0};       // OK: brace-or-equal-initializer is absent.
};

TEST(UTester4StructBitField, CheckHowToInitializeBitField)
{
    BitField bit_field;

    std::cout << "sizeof(BitField) = " << sizeof(BitField) << std::endl;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    printf("bit_field = {%d, %d, %d, %d, %d}\n", bit_field.x1, bit_field.x2, bit_field.y1, bit_field.y3, bit_field.z);
}
