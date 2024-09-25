/*!
 *  \file       test_generalize.c++
 *  \brief      
 *  
 */


#include "generalize.hpp"

#include <vector>
#include <functional>
#include <catch2/catch_test_macros.hpp>

#include "generic_algorithms.hpp"
#include "generic_algorithms.cpp"

TEST_CASE("Make the unit testing for generalizing to algorithms", "[generalize]")
{
    SECTION("Validate whether the add_all() algorithm works well")
    {
        double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
        
        double sum = add_all(numbers, sizeof(numbers)/sizeof(double));
        CAPTURE(sum);
        CHECK(sum == 55.0);
    }
    
    SECTION("Test the generic algorithm: ValueType sum<Iter, ValueType>(Iter first, Iter last)")
    {
    #if false
        std::vector<double> numbers{1.0, 2.0, 3.0, 4.0, 5.0};
        double totals = sum<std::vector<double>::iterator, double>(numbers.begin(), numbers.end());
    #else
        double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
        double totals = sum<double*, double>(numbers, numbers + sizeof(numbers)/sizeof(double));
    #endif
        
        CAPTURE(totals);
        CHECK(totals == 15.0);
    }
    
    SECTION("Verify the function template accumulate()")
    {
        int evens[] = {2, 4, 6, 8, 10};
        auto sum = accumulate<int*, int>(evens, 
                                         evens + sizeof(evens)/sizeof(decltype(evens[0])), 
                                         int{});
        CAPTURE(sum);
        CHECK(sum == 30);
    }
    
    SECTION("Generalize further the function template accumulate()")
    {
        double numbers[] = {1, 2, 3, 4, 5};
        
        auto len = sizeof(numbers)/sizeof(decltype(numbers[0]));
        double sum = accumulate(numbers, 
                                numbers + len,
                                0,
                                std::plus<double>());
    
        double product = accumulate(numbers, numbers+len, 1.0, std::multiplies<double>());
        
        CAPTURE(sum, product);
        CHECK(sum == 15);
        CHECK(product == 120);
    }
}