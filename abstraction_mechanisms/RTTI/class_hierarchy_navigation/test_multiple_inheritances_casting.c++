/*!
 *  \file       test_multiple_inheritances_casting.c++
 *  \brief
 *
 */


#include <CppUTest/TestHarness.h>
#include <iostream>

#include "multiple_inheritances_casting.hpp"

TEST_GROUP(UTest4MultipleInheritancesCasting)
{
};

TEST(UTest4MultipleInheritancesCasting, CheckAmbiguousnessWhenCastingMultipleInheritancesObject)
{
    std::cout << std::endl;

    Radio radio("This is the radio's message");
    try
    {
        cast(radio);
    }
    catch (std::bad_cast& exception)
    {
        std::cerr << __FUNCTION__ << " throws an exception of " << exception.what() << std::endl;
    }

    IStorable* ptr_store = new Radio("radio's message");
    try
    {
        cast(ptr_store);
    }
    catch (std::bad_cast& exception)
    {
        std::cout << __func__ << " throws the exception of " << exception.what() << std::endl;
    }
    delete ptr_store;
}