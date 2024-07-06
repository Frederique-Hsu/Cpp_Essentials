/*!
 *  \file       test_throw_catch_exception.c++
 *  \brief
 *
 */


#include "throw_catch_exception.hpp"

#include <gtest/gtest.h>

TEST(UTest4ThrowException, CheckNoCopyObjCannotBeThrown)
{
    auto fn = [](int n) {
        switch (n)
        {
        case 0: throw MyError{};
        case 1: throw NoCopy{};
        // case 2: throw MyError;
        }
    };
}

TEST(UTest4ThrowException, CheckExceptionStackUnwindingProcess)
{
    auto h = []() {
        std::string s = "not";
        throw MyError{};
        std::string s2 = "at all";
    };

    auto g = [&]() {
        std::string s = "excess";
        {
            std::string s = "or";
            h();
        }
    };

    auto f = [&]() {
        std::string name("Byron");
        try
        {
            std::string s = "in";
            g();
        }
        catch (MyError)
        {
        }
    };

    f();
}

namespace mytest
{
void g(int n)
{
    if (n)
    {
        throw std::runtime_error("I give up!");
    }
    else
    {
        throw MyError2();
    }
}

void f(int n)
{
    try
    {
        g(n);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
}

TEST(UTest4CatchException, CheckCatchUserDefinedException)
{
    EXPECT_THROW( { mytest::g(0); }, MyError2);
    mytest::f(1);
}
