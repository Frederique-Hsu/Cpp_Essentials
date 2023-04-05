/*!
 *  \file       test_vector_container.cpp
 *  \brief
 *
 */


#include "vector_container.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

class Shape
{
};


class VectorUTester : public ::testing::Test
{
protected:
    std::vector<Entry> phone_book = {
        {"David Hume", 123456},
        {"karl Popper", 234567},
        {"Bertrand Arthur William Russel", 345678}
    };
};


TEST_F(VectorUTester, AccessVectorElement)
{
    print_book(phone_book);
}

TEST_F(VectorUTester, DISABLED_AccessingExceedsBoundary)
{
    try
    {
        phone_book[phone_book.size()] = {"Joe Biden", 999999};
    }
    catch (std::out_of_range& exception)
    {
        std::cerr << "Range error!" << std::endl;
    }
}

TEST(UTester4VectorContainer, InitializeVector)
{
    std::vector<int> vint = {1, 2, 3, 4};
    EXPECT_EQ(vint.size(), 4);

    std::vector<std::string> vstr;
    EXPECT_EQ(vstr.size(), 0);

    std::vector<Shape*> vptr(23);
    EXPECT_EQ(vptr.size(), 23);
    EXPECT_EQ(vptr[0], nullptr);

    std::vector<double> vec_numbers(32, 9.9);
    EXPECT_EQ(vec_numbers.size(), 32);;
    EXPECT_DOUBLE_EQ(vec_numbers[0], 9.9);
}
