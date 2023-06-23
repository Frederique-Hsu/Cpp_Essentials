/*!
 *  \file       test_expression_operators.c++
 *  \brief
 *
 */


#include <CppUTest/TestHarness.h>
#include <bitset>
#include <iostream>
#include <vector>

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

TEST(UTester4ExpressionOperators, CheckArithmicOverflow)
{
    int i = 1;
    while (0 < i)   /*! \warning C++的具体实现既不必也不会检查算术运算溢出的问题 */
    {
        ++i;
    }
    /*!
     *  \remark     下溢、上溢和除数为0的错误不会抛出标准异常
     */
    std::cout << "i has become negative! i = " << i << std::endl;
}

int square(int i)
{
    std::cout << "execute the square(int), i = " << i << std::endl;
    return i * i;
}

int cube(int j)
{
    std::cout << "execute the cube(int), j = " << j << std::endl;
    return j * j * j;
}

TEST(UTester4ExpressionOperators, CheckOperationOrder)
{
    /*!
     *  \remark     C++没有明确规定表达式中子表达式的求值顺序。尤其需要注意，你不能假定表达式是
     *              按照从左到右的顺序求值的。
     */
    int sum = square(2) + cube(3);      // 到底先调用square()，还是先调用cube()并没有明确的规定，取决于具体的C++实现
    CHECK_EQUAL(sum, 4 + 27);

    /*============================================================================================*/

    std::vector<int> vec(10);
    int i = 1;
    vec[i] = i++;   // 未定义的结果，有时可能执行未vec[1] = 1, 也有可能执行为vec[2] = 1
    for (size_t index = 0; index != vec.size(); ++index)
    {
        std::cout << "vec[" << index << "] = " << vec[index] << std::endl;
    }

    /*============================================================================================*/
    int a, b;
    /*!
     *  \remark     逗号运算符(,)  逻辑与运算符(&&) 和逻辑或运算符(||)规定他们的左侧运算对象先被求职，然后才是
     *              右侧运算对象。
     */
    b = (a = 2, a + 1);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    CHECK_EQUAL(a, 2);
    CHECK_EQUAL(b, 3);
}
