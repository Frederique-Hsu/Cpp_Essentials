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
