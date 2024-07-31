/*!
 *  \file       Test_String.cpp
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>

#include "String.hpp"

SCENARIO("Make the unit testing for String class", "[String]")
{
    GIVEN("Define a String object")
    {
        String str("abcdefghij");

        THEN("Check the operator<< to print out the string")
        {
            // std::cout << str << std::endl;
            CAPTURE(str);   // similar to call the operator<<
            CHECK(true);
        }

        WHEN("Append the single character to the string")
        {
            str += 'k';     // call "String& operator+=(char c)"

            THEN("Check the operator==(const String& a, const String& b)")
            {
                CAPTURE(str);
                CHECK(str == String("abcdefghijk"));
            }

            str += 'l';

            THEN("Check the operator==(const String& a, const char* str)")
            {
                CAPTURE(str);
                CHECK(str == "abcdefghijkl");
            }

            str += "mn";
            THEN("Check the member function: String& String::operator+=(const char* str) "
                 "works as expected")
            {
                CAPTURE(str);
                CHECK("abcdefghijklmn" == str);
            }
        }
    }

    GIVEN("Define the raw String object, copied_str and moved_str")
    {
        String raw_str = "Hello"_s;     // call "String operator"" _s(const char* str, std::size_t)"
        CHECK(raw_str == "Hello");

        WHEN("Copy the raw_str to the copied_str")
        {
            String copied_str(raw_str);
            THEN("Check the copied_str")
            {
                CAPTURE(copied_str);
                CHECK(copied_str == raw_str);
            }

            String copied_assigned_str("Welcome the C++ programming world!");
            THEN("Check the copy assignment")
            {
                CAPTURE(copied_assigned_str);
                CHECK(copied_assigned_str.size() > copied_str.size());

                copied_assigned_str = copied_str;
                CHECK(copied_assigned_str == "Hello");
                CHECK(copied_assigned_str.size() == copied_str.size());
            }
        }

        WHEN("Move a long string to moved_str")
        {
            String str("Check how the move constructor works, "
                       "and whether it will become empty after "
                       "movement or not?");

            String moved_str = std::move(str);
            THEN("Check the moved string")
            {
                CAPTURE(moved_str);
                CHECK(str.is_empty() == true);
            }
        }

        WHEN("Move a long string and assign the moved_str")
        {
            String str("Implement my own String, and make some optimization");

            String moved_assigned_str("Some raw string, as an example");
            CAPTURE(str.size(),
                    str.capacity(),
                    moved_assigned_str.size(),
                    moved_assigned_str.capacity());

            moved_assigned_str = std::move(str);
            THEN("Check whether the moved and assigned str")
            {
                CAPTURE(str, moved_assigned_str);
                CHECK(str.size() == 0);
            }
        }
    }

    GIVEN("Define a long string to check the range-for loop")
    {
        // Implicit conversion from const str* to String
        String str = "Define a long string to check the range-for loop";
        auto raw_size = str.size();
        auto raw_capacity = str.capacity();

        WHEN("Concatenate the appendix to the string")
        {
            String appendix(", append the appendix.");
            str += appendix;

            THEN("Check whether concatenating two string had succeeded?")
            {
                CAPTURE(str, raw_capacity, str.size(), str.capacity());
                CHECK(str.size() == raw_size + appendix.size());
            }
        }

        WHEN("Iterate the string via range-for-loop")
        {
            int index = 0;
            for (auto iter = begin(str); iter != end(str); ++iter)
            {
                std::cout << *iter;
                CHECK(*iter == str[index++]);
            }
        }
    }

    GIVEN("Enter the string manually by user, and print the string out")
    {
        String user_str("User: ");

        WHEN("User entered some characters into this user_str")
        {
            std::cout << "Please enter some characters from the keyboard, "
                         "and press Ctrl+D to finish.\n"
                      << "注：也支持输入中文。" << std::endl;
            std::cin >> user_str;

            THEN("Print the user_str out")
            {
                std::cout << "\nThe string was printed out as below: " << std::endl;
                std::cout << user_str;
                CHECK(true);
            }
        }
    }
}