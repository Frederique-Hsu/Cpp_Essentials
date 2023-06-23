/*!
 *  \file       test_temporary_object.h++
 *  \brief
 *
 */


#pragma once

#include <CppUTest/TestHarness.h>

TEST_GROUP(UTester4TemporaryObject)
{
public:
    void foo(std::string& s1, std::string& s2, std::string& s3);
    void bar(std::string& s1, std::string& s2, std::string& s3);
    void tor(std::string& s1, std::string& s2);
};
