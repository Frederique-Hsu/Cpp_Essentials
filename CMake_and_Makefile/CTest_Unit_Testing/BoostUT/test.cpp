/*!
 *  \file       test.cpp
 *  \brief
 *
 */


#include <boost/test/unit_test.hpp>

#include "sum_integers.hpp"


BOOST_AUTO_TEST_CASE(check_sum_integers)
{
    auto integers = {1, 2, 3, 4, 5};
    auto result = sum_integers(integers);
    BOOST_TEST(15 == result);
}


BOOST_AUTO_TEST_CASE(CheckMemoryLeaks)
{
    constexpr const int LEN = 5;
    int* p = new int[LEN];

    std::memset(p, 0, sizeof(int) * LEN);

    BOOST_TEST(0 == *p);

    delete[] p;
}
