/*!
 *  \file       test_concepts.c++
 *  \brief      
 *  
 */


#include "Concepts.hpp"
#include "Concepts.cpp"

#include <vector>
#include <list>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Make the unit testing for the find() algorithm to validate whether its concepts can work well", 
          "[find][concepts]")
{
    SECTION("Prepare an array to call the find() function to search the my target element")
    {
        std::vector<int> array{35, 94, 658, -35, 105, -48, -215, 156, 354, -100};
        int target = 156;
        
        // auto iter = my::find(array.begin(), array.end(), target);    // 目前my::find()的概念检查尚未完全实现，待后面实现成功后，再来测试验证。
        auto iter = std::find(array.begin(), array.end(), target);
        // CAPTURE(iter);
        CHECK(*iter == target);
    }
}

TEST_CASE("Validate the value concepts", "[value_concepts]")
{
    SECTION("Check the Small_Size() function template")
    {
        CHECK(Small_Size<5>() == true);
        CHECK(Small_Size<8>() == true);
        CHECK(Small_Size<10>() == false);
    }
}

TEST_CASE("Template Definition Checking", "[concepts_checking]")
{
    SECTION("Check whether the list container has provided the iterator + operation.")
    {
        std::list<int> lst{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        int target = 5;
        auto p = std::find(lst.begin(), lst.end(), target);
        auto q = std::find(vec.begin(), vec.end(), target);
        
        CAPTURE(*p, *q);
        CHECK(*p == target);
        CHECK(*q == target);
    }
}