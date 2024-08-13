/*!
 *  \file   test_Vector.cpp
 *  \brief  perform the unit test for Vector class.
 *  
 */

#include "Vector.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <new>

TEST(VectorUTester, InitializeVectorWithInitializerList)
{
    Vector v1{1, 2, 3, 4, 5};
    EXPECT_EQ(v1.size(), 5);

    Vector v2{1.23, 3.45, 6.7, 8};
    EXPECT_EQ(v2.size(), 4);

    try
    {
        v2[v2.size()] = 10;
    }
    catch (std::out_of_range& exception)
    {
        std::cout << "An exception occurs: " << exception.what() << std::endl;
    }
}

TEST(VectorUTester, CheckNegativeLength)
{
    try
    {
        Vector vec(-27);
    }
    catch (std::length_error& error)
    {
        std::cout << "An error occurs: " << error.what() << std::endl;
    }
    catch (std::bad_alloc& exception)
    {
        std::cout << "An exception occurs: " << exception.what() << std::endl;
    }
}