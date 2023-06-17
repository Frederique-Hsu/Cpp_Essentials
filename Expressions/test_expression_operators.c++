/*!
 *  \file       test_expression_operators.c++
 *  \brief
 *
 */


#include <CppUTest/TestHarness.h>
#include <bitset>
#include <iostream>

TEST_GROUP(UTester4ExpressionOperators)
{
};

TEST(UTester4ExpressionOperators, CheckLogicOperators)
{
    bool x = true;
    bool y = false;

    bool result = x and y;
    CHECK(result == false);
    CHECK_EQUAL(result, x && y);

    result = x or y;
    CHECK_EQUAL(result, true);
    CHECK_EQUAL(x or y, x || y);

    CHECK_EQUAL(not x, false);
    CHECK_EQUAL(not x, !x);

    CHECK_EQUAL(x xor y, true);
}

TEST(UTester4ExpressionOperators, CheckBitLogicOperators)
{
    std::uint8_t a = 0b1001'1011;
    std::int8_t  b = 0b0110'1101;

    auto result = a bitand b;
    CHECK_EQUAL(result, 0b0000'1001);
    CHECK((a bitand b) == (a & b));

    CHECK_EQUAL(sizeof a, 1);
    CHECK_EQUAL(sizeof(std::uint8_t), 1);
    CHECK_EQUAL(sizeof result, sizeof(int));

    result = a bitor b;
    CHECK_EQUAL(result, 0b1111'1111);
    CHECK((a bitor b) == (a | b));

    result = compl a;
    CHECK((compl a) == (~a));
    std::cout << "compl " << std::bitset<8>(a) << " = " << std::bitset<8>(result) << std::endl;
}

TEST(UTester4ExpressionOperators, CheckBitLogicAssignmentOperators)
{
    std::uint16_t a = 0b1101'1011'0010'1001;
    auto result =     0b0110'0101'1010'1101;

    result and_eq a;
    std::cout << "result = 0b" << std::bitset<16>(result) << ", namely 0x" << std::hex << result << std::endl;
    CHECK_EQUAL(result, 0b0100'0001'0010'1001);

    result or_eq a;
    std::cout << "result = 0b" << std::bitset<16>(result) << ", namely 0x" << std::hex << result << std::endl;

    result = 0b0110'0101'1010'1101;
    result xor_eq a;
    std::cout << "result = 0b" << std::bitset<16>(result) << ", namely 0x" << std::hex << result << std::endl;
}
