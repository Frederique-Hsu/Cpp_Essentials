/*!
 *  \file       test_IOStream.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <iostream>

#include "in_stream.h"

TEST(UTester4IOStream, CheckOutStream)
{
    int b = 'b';
    char c = 'c';
    std::cout << 'a' << b << c << std::endl;
}

TEST(UTester4IOStream, DISABLED_CheckInStream)
{
    int i;
    std::cin >> i;

    double d;
    std::cin >> d;

    std::cout << "i = " << i << ", d = " << d << std::endl;
}

TEST(UTester4IOStream, ReadString)
{
#if 1
    hello();
#else
    hello_line();
#endif
}
