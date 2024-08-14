/*!
 *  \file       misc.cpp
 *  \brief      一些杂项
 *
 */



#include <gtest/gtest.h>


TEST(UTester4Misc, CheckObjectDeclaration)
{
    /* char指针的数组 */
    char* kings[] = {"Elizabeth", "Charles", "Edward"};

    /* 指向char数组的指针 */
    char (*presidents)[]; //  = {"Joe Biden", "Donald Trump", "Obama", "Bill Clinton"};
}
