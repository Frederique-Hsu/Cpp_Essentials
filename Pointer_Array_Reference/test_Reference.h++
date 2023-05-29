/*!
 *  \file       test_Reference.h++
 *  \brief
 *
 */


#pragma once

#include <gtest/gtest.h>
#include <vector>
#include <string>


class UTester4Swap : public ::testing::Test
{
protected:
    std::vector<std::size_t> odds;
    std::vector<std::size_t> evens;
public:
    UTester4Swap();
    virtual ~UTester4Swap();
public:
    void SetUp() override;
    void TearDown() override;
};
