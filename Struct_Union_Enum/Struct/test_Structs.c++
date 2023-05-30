/*!
 *  \file       test_Structs.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "Structs.hpp"

TEST(UTester4Structs, AssignStructObject)
{
    Address jd;
    jd.name = "Jim Dandy";
    jd.number = 61;

    Address jim_dandy = {"Jim Dandy",
                         61,
                         "South St.",
                         "New Providence",
                         {'N', 'J'},
                         "07974"};
}