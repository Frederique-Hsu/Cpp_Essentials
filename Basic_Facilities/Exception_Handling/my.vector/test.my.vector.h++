/*!
 *  \file       test.my.vector.h++
 *  \brief      Make the unit test for my::vector<> class template.
 *
 */


#pragma once


#include <gtest/gtest.h>

class UTester4MyVector : public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;
};
