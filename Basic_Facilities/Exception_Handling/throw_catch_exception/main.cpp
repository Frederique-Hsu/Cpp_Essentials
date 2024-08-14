#define BOOST_TEST_MODULE My test module
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(UTest4ThrowException)

BOOST_AUTO_TEST_CASE(CheckNoCopyObjCannotBeThrown)
{
    BOOST_TEST(true /* test assertion */);
}

BOOST_AUTO_TEST_SUITE_END()
