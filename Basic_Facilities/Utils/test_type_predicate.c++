/*!
 *  \file       test_type_predicate.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <utility>

TEST(UTester4Tuple, CheckTupleObjects)
{
    std::tuple<std::string, int, double> tobj("Solid", 12345, 3.1415926);

    auto candidate = std::make_tuple(std::string("Herring"), 10, 1.2345);

    EXPECT_EQ(std::get<0>(candidate), "Herring");
    EXPECT_EQ(std::get<1>(candidate), 10);
    EXPECT_DOUBLE_EQ(std::get<2>(candidate), 1.2345);
}
