/*!
 *  \file   test_operators.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <bitset>
#include <cstring>
#include <iterator>
#include <algorithm>

#include "operators.hpp"

TEST(UTester4BitStream, CheckBitOperators)
{
    ios_base::iostate state = ios_base::iostate::goodbit;

    std::cout << "current state is 0b" << std::bitset<8>(state) << std::endl;
    if (state bitand (ios_base::iostate::badbit | ios_base::iostate::failbit))
    {
        std::cout << "current state is not a good state" << std::endl;
    }

    // state |= ios_base::iostate::eofbit;

    int old = std::cin.rdstate();
    if (std::cin.rdstate() ^ old)
    {
        std::cout << "The stdin console state has changed." << std::endl;
    }
}

TEST(UTester4BitStream, CheckBitFieldComputation)
{
    int x = 0xFF00'FF00;
    short y = middle(x);

    EXPECT_EQ(y, 0x00FF);
}

TEST(UTester4BitStream, CheckStrCopy)
{
    char destination[50] = {0};
    char source[] = "Alice Yu, I love you so much!";

    my::copy(destination, source);
    std::cout << "destination = " << destination << std::endl;

    EXPECT_EQ(std::strlen(source),  std::strlen(destination));

    char dest[100] = {0};
    char *src = "I want to make love with you.";
    std::strcpy(dest, src);
    std::cout << "dest = " << dest << std::endl;

    std::string src_str = "Then we will have a baby.";
    std::string dest_str;
    std::copy(src_str.begin(), src_str.end(), std::back_inserter(dest_str));
    std::cout << "dest_str = " << dest_str << std::endl;
}
