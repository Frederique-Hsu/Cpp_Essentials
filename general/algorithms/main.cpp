/*!
 *  \file       maian.cpp
 *  \brief      Study the algorithms that C++ standrad provides.
 *
 */



#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char* argv[])
{
    return RUN_ALL_TESTS(argc, argv);
}

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
    CHECK("I have passed the 1st CppUTest unit test case.");
}
