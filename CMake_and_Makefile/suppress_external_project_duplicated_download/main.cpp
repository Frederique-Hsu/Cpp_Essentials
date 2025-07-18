/*!
 *  \file       main.cpp
 *  \brief
 *
 */

#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
