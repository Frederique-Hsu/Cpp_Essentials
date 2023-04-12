/*!
 *  \file       test_stream_iterator.c++
 *  \brief
 *
 */


#include <CppUTest/CommandLineTestRunner.h>

#include <iterator>
#include <string>
#include <iostream>

TEST_GROUP(UTester4StreamIterator)
{
};

TEST(UTester4StreamIterator, CheckOutStreamIterator)
{
    /* 将字符串写入cout */
    std::ostream_iterator<std::string> out_stream(std::cout);

    *out_stream = "Hello, ";    // 等价于 cout << "Hello,"
    ++out_stream;
    *out_stream = "world!\n";   // 等价于 cout << "world!\n"

    std::istream_iterator<std::string> in_stream(std::cin);
    std::istream_iterator<std::string> end_of_stream{};
}

