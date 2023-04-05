/*!
 *  \file       test_String.c++
 *  \brief      Make the unit test for String.
 *
 */


#include "String.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


TEST(UTester4String, CheckStringsConcatenation)
{
    auto addr = compose("dmr", "bell-labs.com");
    EXPECT_EQ(addr, "dmr@bell-labs.com");
}

TEST(UTester4String, ManipulateSubString)
{
    std::string name = "Bjarne Stroustrup";

    std::string surname = name.substr(7, 16);
    EXPECT_EQ(surname, "Stroustrup");

    name.replace(0, 6, "nicholas");
    EXPECT_EQ(name, "nicholas Stroustrup");

    name[0] = std::toupper(name[0]);
    EXPECT_EQ(name, "Nicholas Stroustrup");
}
