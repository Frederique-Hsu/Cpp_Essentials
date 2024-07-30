/*!
 *  \file       log_test_messages.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <initializer_list>
#include <sstream>

/*!
 *  \title      Logging macros
 *  \details    Additional messages can be logged during a test case.
 *              Note that the messages logged with \code INFO are scoped, and thus will not be
 *              reported, if failure occurs in scope preceding the message declaration.
 */

TEST_CASE("Foo", "[.Foo]")
{
    INFO("Test case start");

    for (int i = 0; i < 5; ++i)
    {
        INFO("The number is " << i);
        CHECK(i == i);
    }
}

TEST_CASE("Bar", "[.Bar]")
{
    INFO("Test case start");

    for (int i = 0; i < 3; ++i)
    {
        INFO("The number is " << i);
        CHECK(i == i);
    }
    CHECK(false);
}

/*!
 *  \section    Logging without local scope
 *
 *  \details    \code UNSCOPED_INFO is similar to \code INFO with two key differences:
 *
 *  \list
 *      \li     Lifetime of an unscoped message is not tied to its own scope
 *      \li     An unscoped message can be reported by the first following assertion only,
 *              regardless if the result of that assertion.
 *  \endlist
 *
 *              In other words, lifetime of \code UNSCOPED_INFO is limited by the following assertion
 *              (or by the end of test case/section, whichever comes first), whereas lifetime of
 *              \code INFO is limited by its own scope.
 *
 *              These differences make this macro useful for reporting information from helper
 *              functions or inner scopes.
 */
void print_some_info()
{
    UNSCOPED_INFO("Info from helper");
}

TEST_CASE("Baz", "[.Baz]")
{
    print_some_info();

    for (int i = 0; i < 3; ++i)
    {
        UNSCOPED_INFO("The number is " << i);
    }
    CHECK(false);
}

TEST_CASE("Qux", "[.Qux]")
{
    INFO("First info.");
    UNSCOPED_INFO("First unscoped info");
    CHECK(false);

    /*!
     *  \remark     "First unscoped info" message will be cleared after the first \code CHECK
     *              while "First info" message will persist until the end of the test case.
     *              Therefore, when the second \code CHECK fails, 3 messages will be printed.
     */
    INFO("Second info");
    UNSCOPED_INFO("Second unscoped info");
    CHECK(false);
}


/*!
 *  \section    Streaming macros
 *
 *  \details    All these macros allow heterogeneous sequences of values to be streaming using the
 *              insertion operator<< in the same way that std::ostream, std::cout, etc support.
 *
 *  \note       insertion sequence is placed inside the parentheses.
 *
 *  \code INFO(message_expression)
 *
 *  The message is logged to a buffer, but only reported with next assertions that are logged.
 *  This allows you to log contextual information in case of failures, which is not shown during a
 *  successful test run.
 *  Messages are removed from the buffer at the end of their scope.
 *
 *  \code UNSCOPED_INFO(message_expression)
 *
 *  Similar to \code INFO, but messages are not limited to their own scope.
 *  They are removed from the buffer after each assertion, section or test case, whichever comes first.
 *
 *  \code WARN(message_expression)
 *
 *  The message is always reported but does not fail the test.
 *
 *  \code SUCCEED(message_expression)
 *
 *  The message is reported and the test case succeeds.
 *
 *  \code FAIL(message_expression)
 *
 *  The message is reported and test case fails.
 *
 *  \code FAIL_CHECK(message_expression)
 *
 *  As \code FAIL, but does not abort the test.
 */

template<class T>
std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& values)
{
    for (auto& value : values)
    {
        os << value << ",  ";
    }
    os << std::endl;
    return os;
}

template<class T>
std::ostringstream& operator<<(std::ostringstream& oss, const std::vector<T>& values)
{
    for (auto& value : values)
    {
        oss << value << ",  ";
    }
    return oss;
}

TEST_CASE("Log some kinds of message")
{
    SECTION("INFO", "Log the info message")
    {
        int a = 5;
        INFO("a = " << a);
        CHECK(true);
    }

    SECTION("UNSCOPED_INFO", "Log the unscoped info message")
    {
        std::ostringstream oss;
        oss << std::vector<int>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55};

        UNSCOPED_INFO("fibonacci = " << oss.str());
        // CHECK(true);
    }

    SECTION("WARN", "Log the warning message")
    {
        int* numbers = new int[7];
        std::memset(numbers, 0x00, sizeof(int) * 7);

        WARN("*(numbers + 5) = " << *(numbers + 5));

        delete [] numbers;
    }

    SECTION("SUCCEED", "Log the success message")
    {
        SUCCEED("Current C++ standard no. is " << __cplusplus);
    }

#if false
    SECTION("FAIL", "[.][Log the failure message]")
    {
        FAIL("Current program is " << sizeof(void*) * 8 << "-bits.");
    }
#endif
}

/*!
 *  \section    Quickly capture value of variables or expressions
 *
 *  \code   CAPTURE(expression1, expression2, ...)
 *
 *  Sometimes you just want to log a value of variable, or expression. For convenience, we provide
 *  the \code CAPTURE macro, that can take a variable, or an expression, and prints out that
 *  variable/expression and its value at the time of capture.
 *
 *  You can also capture expressions that use commas inside parentheses (e.g. function calls),
 *  brackets, or braces (e.g. initializers). To properly capture expression that contains template
 *  parameters list (in other words, it contains commas between angle brackets), you need to enclose
 *  the expression inside parentheses.
 */

TEST_CASE("Quickly capture value of variables or expressions")
{
    int a = 1, b = 2, c = 3;
    CAPTURE(a, b, c, a+b, c > b, a == 1);

    CAPTURE((std::initializer_list<int>{0, 2, 4, 6, 8, 10}));
    CHECK(true);
}