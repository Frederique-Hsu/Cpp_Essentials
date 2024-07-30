/*!
 *  \file       Test_SmartPointers.c++
 *  \brief      
 *  
 */


#include "SmartPointers.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>

SCENARIO("Make the unit testing for SmartPointers", "[.][smart pointers]")
{
    GIVEN("Provide the structure definition of disk record")
    {
        struct Record
        {
            std::string name;
            // ...
        };

        WHEN("Update the content in the disk")
        {
            auto update = [](const std::string& str) {
                DiskPtr<Record> ptr{str};

                ptr->name = "Roscoe";
            };

            THEN("Expect the disk content will be written, and the pointer will be freed automatically")
            {
                update(std::string("Volume_1"));
                CHECK(true);
            }
        }
    }
}

SCENARIO("Make the unit testing for Ptr", "[Ptr]")
{
    constexpr const std::size_t N = 90;

    GIVEN("Initialize the Ptr with an array")
    {
        std::uint64_t fibonacci[N] = {0x00};
        // CAPTURE(sizeof(std::uint64_t));
        long double golden_ratio_array[N] = {0.0000'0000};
        // CAPTURE(sizeof(long double));

        auto generate = [&fibonacci]() {
            fibonacci[0] = 1;
            fibonacci[1] = 1;

            for (int index = 2; index < sizeof(fibonacci)/sizeof(fibonacci[0]); ++index)
            {
                fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
            }
        };

        auto golden_ratio = [&fibonacci, &golden_ratio_array]() {

            for (auto index = 1; index < sizeof(golden_ratio_array)/sizeof(golden_ratio_array[0]); ++index)
            {
                golden_ratio_array[index] = static_cast<long double>(fibonacci[index-1]) / static_cast<long double>(fibonacci[index]);
            }
        };

        generate();
        std::cout << "\n斐波那契数列： " << std::endl;
        for (auto i = 0; i < N; ++i)
        {
            std::cout << std::setw(25) << fibonacci[i] << "\t";
            if ((i+1) % 5 == 0)
            {
                std::cout << std::endl;
            }
        }

        golden_ratio();
        std::cout << "\n黄金分割点数列： " << std::endl;
        for (auto i = 0; i < N; ++i)
        {
            std::cout << std::setw(25) << std::setprecision(20) << golden_ratio_array[i] << "\t";
            if ((i+1) % 5 == 0)
            {
                std::cout << std::endl;
            }
        }

        Ptr<std::uint64_t> ptr(&fibonacci[0], fibonacci, N);

        WHEN("Move the ptr to check the prefix/postfix self-increment or self-decrement operations")
        {
            ptr++;
            CHECK(*ptr == 1);

            ++ptr;
            CHECK(*ptr == 2);

            ++ptr;
            ++ptr;
            CHECK(*ptr == 5);

            CHECK(*ptr-- == 5);

            CHECK(*--ptr == 2);
        }
    }
}