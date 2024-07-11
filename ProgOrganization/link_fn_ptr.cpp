/*!
 *  \file       link_fn_ptr.cpp
 *  \brief
 *
 */


#include "link_fn_ptr.hpp"

#include <cstdio>
#include <cstdint>

#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <random>

extern "C" int cfn()
{
    std::printf("Link the C function cfn().\n");

    return 0;
}

int cppfn()
{
    return cfn();
}

extern "C" void quick_sort(void* p, size_t n, size_t sz, CFT cmp)
{
    qsort(p, n, sz, cmp);
}

void isort(void* p, size_t n, size_t sz, FT cmp)
{
    std::qsort(p, n, sz, cmp);
}

void xsort(void* p, size_t n, size_t sz, CFT cmp)
{
    quick_sort(p, n, sz, cmp);
}

extern "C" void ysort(void* p, size_t n, size_t sz, FT cmp)
{
    quick_sort(p, n, sz, cmp);
}

int lessThan(const void* a, const void* b)
{
    int* num1 = (int*)a;
    int* num2 = (int*)b;

    if (*num1 < *num2)
        return -1;
    if (*num1 > *num2)
        return 1;
    return 0;
}

extern "C" int greaterThan(const void* a, const void* b)
{
    int* num1 = (int*)a;
    int* num2 = (int*)b;

    if (*num1 < *num2)
        return 1;
    if (*num1 > *num2)
        return -1;
    return 0;
}


static auto printOut = [](int* nums, int len)
{
    for (int index = 0; index < len; ++index)
    {
        std::cout << *(nums + index) << ",  ";
    }
    std::cout << "\n" << std::endl;
};

void sort_i(int* numbers, int sz)
{
    isort(numbers, sz, sizeof(int), lessThan);
    printOut(numbers, sz);

    std::shuffle(numbers, numbers+sz, std::mt19937(std::random_device()()));
    printOut(numbers, sz);

    isort(numbers, sz, sizeof(int), greaterThan);
    printOut(numbers, sz);
}

void sort_x(int* numbers, int sz)
{
    xsort(numbers, sz, sizeof(int), lessThan);
    printOut(numbers, sz);

    std::shuffle(numbers, numbers+sz, std::mt19937(std::random_device()()));
    printOut(numbers, sz);

    xsort(numbers, sz, sizeof(int), greaterThan);
    printOut(numbers, sz);
}

void sort_y(int* numbers, int sz)
{
    ysort(numbers, sz, sizeof(int), lessThan);
    printOut(numbers, sz);

    std::shuffle(numbers, numbers+sz, std::mt19937(std::random_device()()));
    printOut(numbers, sz);

    ysort(numbers, sz, sizeof(int), greaterThan);
    printOut(numbers, sz);
}
