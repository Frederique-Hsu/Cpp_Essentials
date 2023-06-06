/*!
 *  \file       memory_location.cpp
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>

#include "memory_location.hpp"

TEST(UTester4MemoryLocation, CheckMemoryLocationForStruct)
{
    using namespace std;
    cout << "sizeof(S) = " << sizeof(S) << endl;

    S obj;
    printf("S address = 0x%016X\n", (unsigned long long)&obj);
    printf("     &S.a = 0x%016X\n", (unsigned long long)&obj.a);
//    printf("     &S.b = 0x%016X\n", (unsigned int)&obj.b);
//    printf("     &S.c = 0x%016X\n", (unsigned int)&obj.c);
    printf("     &S.e.ee = 0x%016X\n", &obj.e);
}
