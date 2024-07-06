/*!
 *  \file       Text.lib.cpp
 *  \brief
 *
 */


#include "Text.lib.hpp"

#include <new>

namespace TextLib
{
FILE* open(const char* filename)
{
    FILE* fp = fopen(filename, "ar");
    if (fp == nullptr)
    {
        throw std::bad_alloc();
    }
    return fp;
}

void close(FILE* fp)
{
    if (fp != nullptr)
    {
        fclose(fp);
    }
}
}
