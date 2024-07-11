/*!
 *  \file       test.my.string.c++
 *  \brief
 *
 */


#include <CppUTest/TestHarness.h>

#include <cstring>

#include "my.string.hpp"

TEST_GROUP(UTest4MyString)
{
};

TEST(UTest4MyString, CheckStrCpy)
{
    const char* source_str = "Hello World!";

    char target_str[20] = {0x00};

    my::istrcpy(target_str, source_str);

    STRCMP_EQUAL(target_str, "Hello World!");
}

TEST(UTest4MyString, CheckStrCpyWithoutNullTerminator)
{
    char source_str[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    char target_str[20] = {0x00};

    int source_str_total_size = sizeof(source_str);
    int unit_size = sizeof(char);
    int source_str_length = source_str_total_size / unit_size;
    CHECK_EQUAL(source_str_length, 12);

    const char* src = "Hello World!";
    int src_total_size = sizeof(src);
    int src_length = src_total_size / unit_size;
    CHECK_EQUAL(src_length, 8);
    CHECK_EQUAL(strlen(src), 12);

    // my::istrcpy(target_str, source_str);
    std::strcpy(target_str, source_str);
    STRCMP_EQUAL(target_str, "Hello World!");
}

TEST(UTest4MyString, CheckStrCompare)
{
    const char *a = "abc", *b = "abc", *c = "abcd", *d = "abC", *e = "ab";

    CHECK_EQUAL(my::istrcmp(a, b), 0);
    CHECK_TRUE(my::istrcmp(a, c) < 0);
    CHECK_TRUE(my::istrcmp(a, e) > 0);
    CHECK_TRUE(my::istrcmp(a, d) > 0);
}

TEST(UTest4MyString, CheckStrLength)
{
    const char *str = "abcde", *a = "abc\0def";

    CHECK_EQUAL(my::istrlen(str), 5);
    CHECK_EQUAL(my::istrlen(a), 3);
}
