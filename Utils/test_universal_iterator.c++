/*!
 *  \file       test_universal_iterator.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <forward_list>
#include <iostream>

#include "universal_iterator.hpp"

class UTester4UniversalIterator : public ::testing::Test
{
public:
    void test(std::vector<int>& vec, std::forward_list<int>& lst);
};

void UTester4UniversalIterator::test(std::vector<int>& vec, std::forward_list<int>& lst)
{
    sort(vec);      // 排序vector
    // sort(lst);      // 排序单链表
}

TEST_F(UTester4UniversalIterator, CheckUniversalSort)
{
    std::forward_list<int> fwd_list{35, 10, 28, -13, 9, 5, 12, 20, 36, 49, -38, 12};
    std::vector<int> vec{26, 15, -5, 10, 45, -20, 18, 36, -12, 10, 8};

    test(vec, fwd_list);

    std::cout << "Forward directional list was sorted as below: " << std::endl;
    for (auto& element : fwd_list)
    {
        std::cout << element << ", ";
    }
    std::cout << "\n" << std::endl;

    std::cout << "Vector was sorted as below: " << std::endl;
    for (auto& element : vec)
    {
        std::cout << element << ", ";
    }
    std::cout << "\n" << std::endl;
}
