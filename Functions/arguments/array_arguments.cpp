/*!
 *  \file       array_arguments.cpp
 *  \brief
 *
 */


#include "array_arguments.hpp"

#include <gtest/gtest.h>

void compute(int* vec_ptr, int vec_size)
{
    int sum = 0;
    for (int index  = 0; index < vec_size; ++index)
    {
        sum += *(vec_ptr + index);
    }
    std::cout << "sum1 = " << sum << std::endl;
}

void compute(int (&r)[4])
{
    auto size = sizeof(r)/sizeof(int);
    EXPECT_EQ(size, 4);

    int sum = 0;
    for (int index  = 0; index < size; ++index)
    {
        sum += r[index];
    }
    std::cout << "sum2 = " << sum << std::endl;
}
