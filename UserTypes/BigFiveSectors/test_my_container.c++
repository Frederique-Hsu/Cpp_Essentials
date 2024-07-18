/*!
 *  \file       test_my_container.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "my_container.hpp"

TEST_CASE("Make the unit testing for my::Container", "[Container]")
{
    SECTION("Check the default constructor, size() and operator[] methods")
    {
        my::Container<int> empty_container;
        REQUIRE(empty_container.size() == 0);

        my::Container<int> container(5);
        REQUIRE(container.size() == 5);
        for (auto index = 0; index < 5; ++index)
        {
            REQUIRE(container[index] == int{});
        }

        my::Container<int> container_with_init_values(8, -10);
        REQUIRE(container_with_init_values.size() == 8);
        for (auto index = 0; index < 8; ++index)
        {
            REQUIRE(container_with_init_values[index] == -10);
        }
    }

    SECTION("Check the initializer_list constructor")
    {
        std::initializer_list<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        my::Container<int> container(numbers);

        REQUIRE(container.size() == numbers.size());

        unsigned int index = 0;
        for (auto& number : numbers)
        {
            REQUIRE(number == container[index++]);
        }
    }

    SECTION("Check the begin() and end() iterators")
    {
        my::Container<int> fibonacci({1, 1, 2, 3, 5, 8, 13, 21, 34, 55});
        REQUIRE(fibonacci.size() == 10);

        REQUIRE(*fibonacci.begin() == 1);
        REQUIRE(*(fibonacci.begin() + 4) == 5);
        REQUIRE(*(fibonacci.end()-1) == 55);
    }

    SECTION("Check the container with the string type")
    {
        my::Container<std::string> love_oath{"I", "love", "you", "affectionately", ",", "Alice Yu"};
        REQUIRE(love_oath.size() == 6);

        for (auto index = 0; index < love_oath.size(); ++index)
        {
            std::cout << love_oath[index] << " ";
        }
        std::cout << "!\n" << std::endl;
    }
}
