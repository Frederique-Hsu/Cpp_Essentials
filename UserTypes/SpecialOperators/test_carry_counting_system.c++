/*!
 *  \file       test_carry_counting_system.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>

#include "carry_counting_system.hpp"
// #include "user_defined_literal_operator.hpp"

TEST_CASE("Carry out the unit testing for theconversion between "
          "Binary, Hexadecimal, Octal and Decimal")
{
    SECTION("Convert from Hex to Bin")
    {
        using namespace carry_counting_system;

        Hexadecimal hex("5d8A");

        // std::cout << hex.ToBin() << std::endl;
        CAPTURE(hex.ToBin());

        CHECK(hex.ToBin() == Binary("0101110110001010"));

        Hexadecimal hex1 = 6943026_h;
        Hexadecimal hex2 = 0260647004663_H;
        CAPTURE(hex1, hex2);
        CHECK(true);
    }

    SECTION("Convert from Bin to Decimal")
    {
        using namespace carry_counting_system;

        Binary big_bin = 10110101_B;
        Binary small_bin = 010110110101_b;

        CAPTURE(big_bin, small_bin);
        CHECK(true);
    }

    SECTION("处理一个3进制的数，使用模板字面值常量运算符")
    {
        // int ternary_num = 201_b3;
        // CAPTURE(ternary_num);

        // CHECK(true);
    }
}