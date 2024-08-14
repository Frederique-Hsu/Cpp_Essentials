/*!
 *  \file       test_desktop_calculator.c++
 *  \brief
 *
 */



#include <boost/test/unit_test.hpp>

#include <cmath>

BOOST_AUTO_TEST_SUITE(UTest4DesktopCalculator)

BOOST_AUTO_TEST_CASE(CheckHowToOrganizeModularityAndInterfaceByVirtueOfnamespace)
{
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(CheckVariableInitializationAndConcurrency)
{
    int x = 3;
    int y = std::sqrt(++x);

    BOOST_TEST_CHECK(x == 4);
    BOOST_TEST_CHECK(y == 2);
}

BOOST_AUTO_TEST_SUITE_END()
