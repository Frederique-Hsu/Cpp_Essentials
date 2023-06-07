/*!
 *  \file       union.cpp
 *  \brief
 *
 */


#include "union.hpp"

#include <iostream>

void accessUnion(Entry* p)
{
    if (p->t == str)
        std::cout << p->v.s << std::endl;
    else if (p->t == num)
        std::cout << p->v.i << std::endl;
}


int* cheat(int i)
{
    if (sizeof(void*) * 8 == 32)
    {
        Fudge a;
        a.i = i;
        return a.p;
    }
    else
    {
        return reinterpret_cast<int*>(i);
    }
}
