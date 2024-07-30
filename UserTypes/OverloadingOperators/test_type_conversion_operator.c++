/*!
 *  \file       test_type_conversion_operator.c++
 *  \brief
 *
 */



#include <catch2/catch_test_macros.hpp>

#include "type_conversion_operator.hpp"
#include "UniquePtr.hpp"

TEST_CASE("Carry out the unit testing for type-conversion-operator",
          "[type-conversion-operator]")
{
    SECTION("Convert an integer to a class object")
    {
        Tiny c1 = 2;
        CAPTURE(c1);

        Tiny c2 = 62;
        CAPTURE(c2);

        Tiny c3 = c2 - c1;  // c3 = 60
        CAPTURE(c3);

        Tiny c4 = c3;
        CAPTURE(c4);

        int i = c1 + c2;
        CAPTURE(i);

#if false
        CHECK_THROWS_AS(Tiny(0b0101'1101), Tiny::BadRange);
#else
        try
        {
            Tiny myTinyInt = 0b0101'1101;
        }
        catch (Tiny::BadRange& exception)
        {
            std::cout << exception.what() << std::endl;
        }
#endif

        CHECK_THROWS_AS(c1 = c1 + c2, Tiny::BadRange);

        i = c3 - 64;
        CHECK(i == -4);

        CHECK_THROWS_AS(c2 = c3 - 64, Tiny::BadRange);
        c3 = c4;
        UNSCOPED_INFO("c3 := " << c3);
        CHECK(true);
    }

    SECTION("Enter the number from the keyboard by user to construct the Tiny object")
    {
        Tiny obj;

        try
        {
            std::cin >> obj;
        }
        catch (Tiny::BadRange& exception)
        {
            std::cout << exception.what() << std::endl;
        }
        CAPTURE(obj);
        CHECK(true);
    }

    SECTION("Check the explicit type conversion for user-define UniquePtr class")
    {
        UniquePtr<int> pointer(new int{9});
        if (!pointer)
        {
            throw std::invalid_argument("Allocating memory for unique_ptr failed.");
        }

        CAPTURE(pointer);
        CHECK(true);
    }
}

class X
{
public:
    X(int) {}
    X(const char*) {}
};

class Y
{
public:
    Y(int) {}
};

class Z
{
public:
    Z(X) {}
};

X fn(X xobj)
{
    return xobj;
}
Y fn(Y yobj)
{
    return yobj;
}
Z gc(Z zobj)
{
    return zobj;
}

class XX
{
public:
    XX(int i)
    {
        std::cout << "Called XX(int = " << i << ")" << std::endl;
    }
};

void hg(double d)
{
    std::cout << "Called hg(double = " << d << ")" << std::endl;
}
void hg(XX xobj)
{
    std::cout << "Called hg(XX)" << std::endl;
}

SCENARIO("Check the ambiguousness for the type conversion")
{
    GIVEN("Define a common function")
    {
        auto call = []() {
            // fn(1);      // Error: ambiguous, is fn(X(1)) or fn(Y(1))?
            fn(X{1});       // OK
            fn(Y{1});       // OK
            // gc("Mack");     // Error: two user-defined conversion needed: gc(Z{X{"Mack}})
            gc(X{"Doc"});   // OK: gc(Z{X{"Doc"}})
            gc(Z{"Suzy"});  // OK: gc(Z{X{"Suzy"}})
        };
        THEN("Call and check")
        {
            call();
            CHECK(true);
        }
    }

    GIVEN("Define the class XX and the overloaded hg function")
    {
        THEN("Which edition of hg will be called?")
        {
            hg(1);
            hg(XX{1});
            CHECK(true);
        }
    }
}