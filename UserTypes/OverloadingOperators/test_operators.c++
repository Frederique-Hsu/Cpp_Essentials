/*!
 *  \file       test_operators.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>

#include "operators.hpp"

TEST_CASE("Check the operator overloading for complex class", "[complex operators]")
{
    SECTION("Execute the complex + and * calculation, check whether their calculation are correct?")
    {
        complex a = complex{1, 3.1};
        complex b{1.2, 2};
        complex c{b};

        a = b + c;
        CAPTURE(a);

        CHECK(a.real() == 2.4);
        CHECK(a.imag() == 4);

        b = b + c * a;
        CAPTURE(b);

        c = a * b + complex(1, 2);
        CAPTURE(c);
        CHECK(true);
    }

    SECTION("CHeck the member and non-member operators")
    {
        auto fn = [](complex x, complex y, complex z)
        {
            complex r1{x + y + z};
            CAPTURE(r1);

            complex r2{x};
            CAPTURE(r2);

            r2 += y;
            CAPTURE(r2);

            r2 += z;
            CAPTURE(r2);

            CHECK(true);
        };

        complex x{1, 2}, y{3, 4}, z{5, 6};
        fn(x, y, z);

        auto gc = [](complex x, complex y) {
            auto r1 = x + y;
            CAPTURE(r1);

            auto r2 = x + 2;
            CAPTURE(r2);

            auto r3 = 2 + x;
            CAPTURE(r3);

            auto r4 = 2 + 4;
            CAPTURE(r4);

            CHECK(true);
        };

        gc(x, y);
    }

    SECTION("Check the user-defined literal suffixes")
    {
        complex z1{2.4, 1e03};
        constexpr complex z2{92, -36e-04};

        CAPTURE(z1);
        CAPTURE(z2);

        complex comp{1.2 + 25e2i};      // user-defined literal
        CAPTURE(comp);

        auto literal_fn = [](double d) -> complex
        {
            auto x{2.3i};

            return x + sqrt(d + 12e0i) + 12e1i;
        };

        auto result = literal_fn(5);
        CAPTURE(result);

        CHECK(true);
    }
}

SCENARIO("Study how to define and use the operator overloading", "[operator]")
{
    GIVEN("Define the unary operator")
    {
        class X
        {
        public:
            void operator=(const X&) = delete;
            // void operator&() = delete;
            void operator,(const X&) = delete;
        public:
            X* operator&();         // prefix unary & (address of)
            X operator&(X);         // binary & (and)
            X operator++(int);      // postfix increment
            // X operator&(X, X);   // Error: ternary
            // X operator/();       // Error: unary/
        };

        X operator-(X);             // prefix unary minus
        X operator-(X, X);          // binary minus
        X operator--(X&, int);      // postfix decrement
        // X operator-();           // Error: no operand
        // X operator-(X, X, X);    // Error: ternary
        // X operator%(X);          // Error: unary %
    }
}