/*!
 *  \file       meta_functions.cpp
 *  \brief      
 *  
 */


#include "meta_functions.hpp"

#include <iostream>
#include <cstdint>

constexpr int factorial_sum(int n)
{
    int sum = 0;
    int fact = 1;
    for (int i = 1; i <= n; ++i)
    {
        fact *= i;
        sum += fact;
    }
    return sum;
}

void print_factorial_sum()
{
    constexpr int array[] =   {                0,  factorial_sum(1),   factorial_sum(2), factorial_sum(3), factorial_sum(4),
                                factorial_sum(5),  factorial_sum(6),   factorial_sum(7), factorial_sum(8), factorial_sum(9),
                               factorial_sum(10), factorial_sum(11),  factorial_sum(12)};
    for (int n; std::cin >> n; )
    {
        std::cout << array[n] << std::endl;
    }
}

void misc()
{
    std::uint32_t uint32_max_value = 0xFFFF'FFFF;
    std::int32_t   int32_min_value = 0x7FFF'FFFF;
    
    int factorial_sum_12 = 5'2295'6313;
    
    std::cout << "uint32_max_value = " << uint32_max_value << std::endl
              << "int32_min_value = " << int32_min_value << std::endl
              << "factorial_sum_12 = " << factorial_sum_12 << std::endl;
}
