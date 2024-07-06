/*!
 *  \file       test_assertion.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <limits>

#include "assertion.hpp"

TEST(UTest4Assertion, CheckDynamicAssertion)
{
    auto f1 = [](int n)
    /*!
     *  \brief      Check the precondition for function's arguments should meet some requirements.
     *  \param      n   should be within this scope [1, max).
     */
    {
        Assert::dynamic<Assert::level(2), Assert::Error>(
            (0 < n && n < std::numeric_limits<int>::max()),
            Assert::compose(__FILE__, __FUNCTION__, __LINE__, "range problem"));
    };

    f1(-5);

    auto f2 = [](int n) {
        Assert::dynamic((0 < n && n < std::numeric_limits<int>::max()),
                        Assert::compose(__FILE__, __FUNCTION__, __LINE__, "range problem"));
    };

    f2(5);

    auto f3 = [](int n) {
        Assert::dynamic(0 < n && n < std::numeric_limits<int>::max());
    };

    f3(0);
}
