/*!
 *  \file       test_initialization.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "initialization.hpp"

SCENARIO("Direct and copy initialization", "[Init]")
{
    GIVEN("A nested container")
    {
        #include <vector>

        using namespace std;
        vector<vector<double>> vec2D = {
            {10, 11, 12, 13, 14, 15},       // OK: vector of 6 elements
            {10.20},                        // OK: vector of 1 element
            // 10,                          // Error: vector<double>(int) is explicit
            vector<double>{1, 2, 3, 4, 5},  // OK: vector of 5 elements
            vector<double>{10},             // OK: vector of 1 element with value 0.0
            vector<double>(10)              // OK: vector of 10 elements with value 0.0
        };

        for (auto row_index = 0U; row_index < vec2D.size(); ++row_index)
        {
            std::cout << "vec2D[" << row_index << "] has "
                      << vec2D[row_index].size() << " elements." << std::endl;
        }
        std::cout << "\n" << std::endl;

        WHEN("Assign the initializer to a container")
        {
            vector<double> v1{7, 8, 9};
            REQUIRE(v1.size() == 3);
            vector<double> v2 = {9, 8, 7};

            auto fn = [&v2](const vector<double>& arg) {
                v2 = arg;
            };

            THEN("Whether can change or replace the raw container?")
            {
                v1 = {10, 11, 12, 13, 14};
                REQUIRE(v1.size() == 5);
                REQUIRE(*v1.begin() == 10);
                REQUIRE(v1[v1.size()-1] == 14);

                fn({1, 2, 3, 4, 5});
                REQUIRE(v2.size() == 5);
                REQUIRE(v2[0] == 1);
                REQUIRE(v2[4] == 5);
            }

            vector<string> strvec1{"Anya"};
            vector<string> strvec2 = {"Counrtney"};

            auto replace = [&strvec2](const vector<string>& args) {
                strvec2 = args;
            };

            THEN("Expect to change or replace the raw container")
            {
                strvec1 = {"Frederique", "Hsu"};
                REQUIRE(strvec1[0] == "Frederique");
                REQUIRE(strvec1[1] == "Hsu");

                replace({"Xu", "Zan"});
                REQUIRE(strvec2.size() == 2);
            }
        }
    }
}

SCENARIO("Member and Base Initialization")
{
    GIVEN("Two base classes, one has default constructor, but another has no default constructor")
    {
        class Father
        {
        public:
            Father() {}     // has default constructor
        };

        class Mother
        {
        public:
            Mother(int) {}  // has no default constructor
        };

        WHEN("A derived class inherits from both of them")
        {
            struct Son : Father, Mother
            {
                Son(int number) : Father{}, Mother{number}  // Explicitly use both Father and Mother
                {
                }
            };

            struct Daughter : Father, Mother
            {
                Daughter(int num) : Mother{num}     // Father{} is used implicitly, can omit
                {
                }
            };

        #if false
            struct Child : Father, Mother
            {
                Child(int no)   // Error: Mother requires an int initializer.
                {
                }
            };
        #endif
        }
    }
}

TEST_CASE("Make the unit testing for delegating constructor and initialization", "[delegate]")
{
    SECTION("调用被委托构造函数")
    {
        Delegate man(360);
        REQUIRE(man.getNumber() == 360);
    }

    SECTION("Call the default constructor, but it then invoke the delegating constructor")
    {
        Delegate obj;

        REQUIRE(obj.getNumber() == 42);
    }

    SECTION("Call the ordinary constructor, then it goes to invoke the delegating constructor")
    {
        Delegate number{"125"};

        REQUIRE(number.getNumber() == 125);
    }

    SECTION("Call the constructor, but pass an invalid argument")
    {
        REQUIRE_THROWS_AS(Delegate(-10), std::invalid_argument);
    }
}

SCENARIO("Inside-class initializer")
{
    GIVEN("Define a simple class, which does not contain the non-static member")
    {
        /*!
         *  \note   类中初始化器
         *          可以在类声明中为非static数据成员指定初始化器。
         *          {}和=语法能够用于类中初始化器，但()语法就不行。因为它()会被编译器看成是函数。
         */
        class Simple
        {
            int a{18};
            int b = 72;
        public:
            Simple() {}

            int getMemberA() const
            {
                return a;
            }
            int getMemberB() const
            {
                return b;
            }
        };

        THEN("Check the inside-class initialization can work as expected")
        {
            Simple obj;
            REQUIRE(obj.getMemberA() == 18);
            REQUIRE(obj.getMemberB() == 72);
        }
    }
}
