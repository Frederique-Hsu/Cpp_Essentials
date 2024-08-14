/*!
 *  \file       link_fn_ptr.hpp
 *  \brief
 *
 */


#pragma once

#include <cstddef>

int cppfn();

typedef int (*FT)(const void*, const void*);                    // FT采用C++链接

extern "C" {
    typedef int (*CFT)(const void*, const void*);               // CFT采用C链接
    void quick_sort(void* p, size_t n, size_t sz, CFT cmp);     // cmp采用C链接
}

void isort(void* p, size_t n, size_t sz, FT cmp);               // cmp采用C++链接
void xsort(void* p, size_t n, size_t sz, CFT cmp);              // cmp采用C链接
extern "C" void ysort(void* p, size_t n, size_t sz, FT cmp);    // cmp采用C++链接

int lessThan(const void*, const void*);                         // lessThan()采用C++链接
extern "C" int greaterThan(const void*, const void*);           // greaterThan()采用C链接

extern "C" void shuffle(void* array, int length);

void sort_i(int* numbers, int sz);
void sort_x(int* numbers, int sz);
void sort_y(int* numbers, int sz);
