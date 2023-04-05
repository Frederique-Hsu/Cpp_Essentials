/*!
 *  \file       main.cpp
 *  \brief      Study some basic container of C++.
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    catch (...)
    {
        std::cerr << "Unknown exception thrown!" << std::endl;
    }
}
