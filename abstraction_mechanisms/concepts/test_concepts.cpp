/*!
 *  \file       test_concepts.cpp
 *  \brief      
 *  
 */


#include "concepts.hpp"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <vector>
#include <list>

TEST_CASE("Check how concepts of template's type argument work", "[concepts]")
{
    enum class MyEnum
    {
        A,
        B,
        C
    };

    SECTION("Verify the user-defined concepts")
    {
        int num = 10;
        MyEnum kind{MyEnum::B};
        std::vector<int> ivec = {1, 2, 3, 4, 5};

        print_and_increment(num, ivec);

        // print_and_increment(kind, ivec);    // Error: 'MyEnum' does not satisfy the 'IncrementableAndPrintable' constraint.
        CHECK(true);
    }
}

SCENARIO("Implement a function template with the concept to require type argument", "[copy]")
{
    GIVEN("Define a container")
    {
        std::vector<int> fibonacci;

        auto generate = [&fibonacci](int container_size)
        {
            if (container_size < 2)
            {
                throw std::length_error("The container's size should at least exceed 2.");
            }
            fibonacci.resize(container_size);
            fibonacci[0] = 1;
            fibonacci[1] = 1;
            for (auto index = 2; index < container_size; ++index)
            {
                fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
            }
        };

        WHEN("Reserve another container to accommodate the items")
        {
            std::list<std::uint64_t> numbers;

            generate(10);

            THEN("Copy from the fibonacci container to the numbers container")
            {
                auto outIter = user_copy(fibonacci.begin(), fibonacci.end(), std::back_inserter(numbers));
                // CAPTURE(outIter);

                std::size_t size = fibonacci.size();
                auto index = 0U;
                for (auto iter = numbers.begin(); iter != numbers.end(); ++iter)
                {
                    if (index >= size)
                    {
                        break;
                    }
                    CHECK(*iter == fibonacci[index++]);
                }
            }
        }
    }
}
