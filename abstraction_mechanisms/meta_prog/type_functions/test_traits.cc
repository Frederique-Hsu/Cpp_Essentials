/*!
 *  \file       test_traits.cc
 *  \brief      
 *  
 */


#include "traits.hpp"

#include <boost/test/unit_test.hpp>

#include <vector>
#include <random>


BOOST_AUTO_TEST_SUITE(UTest4Traits)

    BOOST_AUTO_TEST_CASE(CheckBinarySearch)
    {
        auto generateFibonacci = [](int count) 
        {
            if (count <= 2)
            {
                return std::vector<int>();
            }
            std::vector<int> fibonacci(count);
            fibonacci[0] = 1;
            fibonacci[1] = 1;
            for (int index = 2; index < count; ++index)
            {
                fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
            }
            return fibonacci;
        };

        std::vector<int> fibonacci = generateFibonacci(40);

        int target = 987;
        std::vector<int>::iterator result = Binary_Search(fibonacci.begin(), fibonacci.end(), target);

        BOOST_CHECK(*result == target);

        std::shuffle(fibonacci.begin(), fibonacci.end(), std::mt19937(std::random_device{}()));
        result = Search(fibonacci.begin(), fibonacci.end(), 28657);
        BOOST_CHECK(*result == 28657);
    }

BOOST_AUTO_TEST_SUITE_END()