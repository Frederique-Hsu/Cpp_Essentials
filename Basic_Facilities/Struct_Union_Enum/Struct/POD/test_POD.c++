/*!
 *  \file       test_POD.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "pod.hpp"

TEST(UTester4POD, CheckWhetherUserDefinedTypeIsPOD)
{
    EXPECT_EQ(std::is_pod<S0>::value, true);
    EXPECT_EQ(std::is_pod<S1>::value, true);
    EXPECT_EQ(std::is_pod<S2>::value, false);
    EXPECT_EQ(std::is_pod<S3>::value, false);
    EXPECT_EQ(std::is_pod<S4>::value, true);
    EXPECT_EQ(std::is_pod<S5>::value, false);
    EXPECT_EQ(std::is_pod<S6>::value, true);
    EXPECT_EQ(std::is_pod<S7>::value, true);
    EXPECT_EQ(std::is_pod<S8>::value, false);
    EXPECT_EQ(std::is_pod<S9>::value, true);
}