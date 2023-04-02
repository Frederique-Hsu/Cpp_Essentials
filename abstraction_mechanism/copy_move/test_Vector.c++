/*!
 *  \file   test_Vector.c++
 *  \brief  Make the unit test for Vector class.
 *  
 */

#include "Vector.hpp"

#include <gtest/gtest.h>

CopyMove::Vector func()
{
    CopyMove::Vector x(1000);
    CopyMove::Vector y(1000);
    CopyMove::Vector z(1000);

    z = x;              /* 执行拷贝操作 */
    y = std::move(x);   /* 执行移动操作 */

    return z;           /* 执行移动操作 */
}

CopyMove::Vector copy_move(CopyMove::Vector& x, CopyMove::Vector& y, CopyMove::Vector& z)
{
    z = x;
    y = std::move(x);

    return z;
}

TEST(UTester4Vector, TestMoveOperation)
{
    CopyMove::Vector result = func();
    EXPECT_EQ(result.size(), 1000);
}

TEST(UTester4Vector, TestCopyAndMoveOperations)
{
    CopyMove::Vector x(5000);
    CopyMove::Vector y(5000);
    CopyMove::Vector z(5000);

    CopyMove::Vector result = copy_move(x, y, z);
    EXPECT_EQ(result.size(), 5000);
    EXPECT_EQ(x.size(), 0);
    EXPECT_EQ(z.size(), 5000);
    EXPECT_EQ(y.size(), 5000);
}