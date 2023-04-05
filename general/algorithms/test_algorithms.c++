/*!
 *  \file       test_algorithms.c++
 *  \brief
 */


#include <CppUTest/CommandLineTestRunner.h>

#include "algorithms.hpp"

TEST_GROUP(StdAlgorithmsUTester)
{
protected:
    std::vector<Entry> phone_book = {
        {"David Hume", 123456},
        {"Karl Popper", 234567},
        {"Bertrand Arthur William Russel", 345678},
        {"Bjarne Stroustrup", 234567},
        {"Steve Jobs", 456789},
        {"Elisabeth Robson", 123456},
        {"Eric Freeman", 135790}
    };
};

TEST(StdAlgorithmsUTester, CheckSortAndUniqueCopyAlgos)
{
    std::list<Entry> lst(7);
    unique_sort_copy(phone_book, lst);

    CHECK_TRUE(lst.size() == 7);

    // std::cout << lst << std::endl;
}

TEST(StdAlgorithmsUTester, CheckSortAndUniqueAppendAlgos)
{
    std::list<Entry> resultList = unique_sort_append(phone_book);
    CHECK_EQUAL(resultList.size(), 7);
}
