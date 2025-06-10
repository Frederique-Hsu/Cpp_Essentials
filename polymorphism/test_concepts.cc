/*!
 *  \file       test_concepts.cc
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "concepts.hpp"

TEST(UTester4Concepts, CheckFoo)
{
    foo5(1);

    // foo5(bar{});    // bar does not satisfy 'has_increment'
}