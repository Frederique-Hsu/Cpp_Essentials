/*!
 *  \file       test_entry.c++
 *  \brief
 *
 */


#include "entry.hpp"
#include "test_entry.h++"

#include <gtest/gtest.h>

TEST(UTester4Entry, CheckHowToInstantiateEntry)
{
    my::Entry number_entry(15);
    EXPECT_EQ(number_entry.number(), 15);

    my::Entry text_entry("text");
    EXPECT_EQ(text_entry.text(), std::string("text"));
}

TEST_F(EntryUTester, SetEntryNewPropertyValue)
{
    EXPECT_EQ(number_entry.number(), 20);

    number_entry.set_number(55);
    EXPECT_EQ(number_entry.number(), 55);

    number_entry.set_text("number");
    EXPECT_EQ(number_entry.text(), "number");
    EXPECT_THROW(number_entry.number(), my::Entry::Bad_entry);

    /*========================================================================*/

    EXPECT_EQ(text_entry.text(), "entry with union of string");

    text_entry.set_text("entry text");
    EXPECT_EQ(text_entry.text(), "entry text");

    text_entry.set_number(2023);
    EXPECT_EQ(text_entry.number(), 2023);

    EXPECT_THROW(text_entry.text(), my::Entry::Bad_entry);
}

TEST_F(EntryUTester, CheckHowToCopyEntry)
{
    my::Entry newly_copied_number_entry(number_entry);
    EXPECT_EQ(newly_copied_number_entry.number(), 20);

    my::Entry newly_copied_text_entry(text_entry);
    EXPECT_EQ(newly_copied_text_entry.text(), "entry with union of string");
}

TEST_F(EntryUTester, CheckHowToAssignNewEntry)
{
    my::Entry newly_assigned_number_entry(1024);
    EXPECT_EQ(newly_assigned_number_entry.number(), 1024);

    newly_assigned_number_entry = number_entry;
    EXPECT_EQ(newly_assigned_number_entry.number(), 20);

    /*========================================================================*/

    my::Entry newly_assigned_text_entry("text");
    EXPECT_EQ(newly_assigned_text_entry.text(), "text");

    newly_assigned_text_entry = text_entry;
    EXPECT_EQ(newly_assigned_text_entry.text(), "entry with union of string");

    /*========================================================================*/

    newly_assigned_number_entry = text_entry;
    EXPECT_EQ(newly_assigned_number_entry.text(), "entry with union of string");

    newly_assigned_text_entry = number_entry;
    EXPECT_EQ(newly_assigned_text_entry.number(), 20);
}
