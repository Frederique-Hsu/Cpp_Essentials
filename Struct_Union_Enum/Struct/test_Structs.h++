/*!
 *  \file       test_Structs.h++
 *  \brief      
 *  
 */


#pragma once

#include <gtest/gtest.h>

#include "Structs.hpp"
#include "array.hpp"

class UTester4StructArray : public ::testing::Test
{
public:
    using Array = array<Point, 3>;

    Array shift(Array a, Point p);
protected:
    Array points{Point{1, 2}, Point{3, 4}, Point{5, 6}};
};