/*!
 *  \file       catch2_unit_test.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>

#include <iostream>


unsigned int Factorial(unsigned int number)
{
    return number > 1 ? Factorial(number-1) * number : 1;
}


TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(0) == 1);
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 362'8800);
}

TEST_CASE("vectors can be sized and resized", "[vector]")
{
    std::vector<int> vec(5);

    REQUIRE(vec.size() == 5);
    REQUIRE(vec.capacity() >= 5);
    std::cout << "vec.capacity() = " << vec.capacity() << std::endl;

    SECTION("resizing bigger changes size and capacity")
    {
        vec.resize(10);

        REQUIRE(vec.size() == 10);
        REQUIRE(vec.capacity() >= 10);
        std::cout << "vec.capacity() = " << vec.capacity() << std::endl;
    }

    SECTION("resizing smaller changes size but not capacity")
    {
        vec.resize(2);

        REQUIRE(vec.size() == 2);
        std::cout << "vec.capacity() = " << vec.capacity() << std::endl;
        REQUIRE(vec.capacity() >= 5);
    }

    SECTION("reserving bigger changes capacity but not size")
    {
        vec.reserve(10);

        REQUIRE(vec.size() == 5);
        std::cout << "vec.capacity() = " << vec.capacity() << std::endl;

        SECTION("reserving down unused capacity does not change capacity")
        {
            vec.reserve(7);
            REQUIRE(vec.size() == 5);
            REQUIRE(vec.capacity() == 10);
        }
    }
}

SCENARIO("vectors can be sized and resized", "[vector]")
{
    GIVEN("A vector with some items")
    {
        std::vector<int> ivec(5);

        REQUIRE(ivec.size() == 5);
        REQUIRE(ivec.capacity() >= 5);

        WHEN("the size is increased")
        {
            ivec.resize(10);

            THEN("the size and capacity change")
            {
                REQUIRE(ivec.size() == 10);
                REQUIRE(ivec.capacity() >= 10);
            }
        }

        WHEN("the size is reduced")
        {
            ivec.resize(0);

            THEN("the size changes, but not capacity")
            {
                REQUIRE(ivec.size() == 0);
                REQUIRE(ivec.capacity() >= 5);
            }
        }

        WHEN("more capacity is reserved")
        {
            ivec.reserve(10);

            THEN("the capacity changes, but not the size")
            {
                REQUIRE(ivec.size() == 5);
                REQUIRE(ivec.capacity() >= 10);
            }
        }

        WHEN("less capacity is reserved")
        {
            ivec.reserve(0);

            THEN("neither size nor capacity are changed")
            {
                REQUIRE(ivec.size() == 5);
                REQUIRE(ivec.capacity() >= 5);
            }
        }
    }
}
