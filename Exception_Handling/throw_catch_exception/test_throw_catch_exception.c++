/*!
 *  \file       test_throw_catch_exception.c++
 *  \brief
 *
 */

#define BOOST_TEST_MODULE test_throw_catch_exception

#include <boost/test/included/unit_test.hpp>

#include "throw_catch_exception.hpp"

BOOST_AUTO_TEST_SUITE(UTest4ThrowException)

BOOST_AUTO_TEST_CASE(CheckNoCopyObjectCannotBeThrown)
{
    auto fn = [](int n) {
        switch (n)
        {
        case 0: throw MyError{};
        // case 1: throw NoCopy{};
        // case 2: throw MyError;
        }
    };

    fn(0);
}

BOOST_AUTO_TEST_SUITE_END()
