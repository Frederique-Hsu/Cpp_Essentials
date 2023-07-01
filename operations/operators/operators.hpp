/*!
 *  \file       operators.hpp
 *  \brief
 *
 */



#pragma once

#include <cstdint>
#include <stdexcept>

class ios_base
{
public:
    enum iostate
    {
        goodbit     = 0b0000'0000,
        eofbit      = 0b0000'0001,
        failbit     = 0b0000'0010,
        badbit      = 0b0000'0100
    };
};

constexpr unsigned short middle(int a)
/*!
 *  \warning    constexpr函数一般要求是inline内联的，原型与实现不能分离。
 */
{
    static_assert(sizeof(int) == 4, "unexpected int size");
    static_assert(sizeof(short) == 2, "unexpected short size");

    return (a >> 8) & 0xFFFF;
}

namespace my
{
void copy(char* dest, const char* src);
char* strcpy(char*, const char*);
}
