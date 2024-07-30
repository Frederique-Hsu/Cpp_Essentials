/*!
 *  \file       test_user_defined_literal_operator.cpp
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "user_defined_literal_operator.hpp"


template<typename T> void print(const T& obj)
{
    std::cout << obj << "\n" << std::endl;
}

TEST_CASE("Check the string literal operator", "[literal_operator]")
{
    SECTION("Pass into the string literal value, to check whether it will print out correctly?")
    {
        print("Hello");
        print("Hello"_s);
        print("Hello,Fengying,\n I love you so much!"_s);

        auto z = 2 + 1i;
        print(z);

        CHECK(true);
    }

    SECTION("Check the big number literal operator")
    {
        using namespace Numerics::literals;

        print(1681652486354268910534987885645205489129864156_x);

        CHECK(true);
    }

    SECTION("Check the sum of 2 big numbers with different length")
    {
        using namespace Numerics::literals;

        Numerics::BigNum bignum_a =     5845684165198165158841_x;
        Numerics::BigNum bignum_b = 84686236528474615210250549_x;

        std::string sum = bignum_a + bignum_b;

        std::cout << Numerics::BigNum(sum.c_str());

        CHECK(Numerics::BigNum(sum.c_str()) == 84692082212639813375409390_x);
    }

    SECTION("Check the sum of 2 big numbers with same length")
    {
        using Numerics::BigNum;
        using namespace Numerics::literals;

        BigNum bignum_a = 5845684165198165158841_x;
        BigNum bignum_b = 6236528474615210250549_x;

        std::string sum = bignum_a + bignum_b;
        std::cout << BigNum(sum.c_str());

        CHECK(BigNum(sum.c_str()) == 12082212639813375409390_x);
    }

    SECTION("Check more string literal variables")
    {
        std::string s1 = "one two"_s;
        std::string s2 = "two\ntwo"_s;
        std::string s3 = R"(two\ntwo)"_s;

        CAPTURE(s1, s2, s3);
        CHECK(s3.length() == 8);
    }
}