/*!
 *  \file       test_entry.h++
 *  \brief
 *
 */


#pragma once

#include <gtest/gtest.h>

#include "entry.hpp"

class EntryUTester : public ::testing::Test
{
protected:
    my::Entry number_entry{20};
    my::Entry text_entry{"entry with union of string"};
public:
};
