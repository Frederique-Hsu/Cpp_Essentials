/*!
 *  \file       memory_location.hpp
 *  \brief
 *
 */


#pragma once

struct S
{
    char        a;
    int         b : 5;
    unsigned    c : 11;
    unsigned      : 0;
    unsigned    d : 8;
    struct {
        int     ee : 8;
    }           e;
};
