/*!
 *  \file       test_Structs.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "Structs.hpp"
#include "array.hpp"
#include "test_Structs.h++"


TEST(UTester4Structs, CheckInstantiateStructObject)
{
    // Points x0;      // 错误： 缺少默认构造函数

    Points x1({100, 200});
    Points x2{{100, 200}, {200, 400}};
}

TEST(UTester4Structs, CheckStructArray)
{
    using Array = array<Point, 3>;

    Array points{Point{1, 2}, Point{3, 4}, Point{5, 6}};
    int x2 = points[2].x;
    int y2 = points[2].y;

    EXPECT_EQ(x2, 5);
    EXPECT_EQ(y2, 6);
}

UTester4StructArray::Array UTester4StructArray::shift(Array a, Point p)
{
    for (auto i = 0U; i != a.size(); ++i)
    {
        a[i].x += p.x;
        a[i].y += p.y;
    }
    return a;
}

TEST_F(UTester4StructArray, CheckShiftStructArray)
{
    Array ax = shift(points, Point{10, 20});

    print(ax);
}