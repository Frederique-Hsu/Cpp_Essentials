/*!
 *  \file       Structs.hpp
 *  \brief
 *
 */


#pragma once

struct Address
{
    const char* name;
    int number;
    const char* street;
    const char* town;
    char state[2];
    const char* zip;
};
