/*!
 *  \file       test_parameterization_hierarchy.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "class_hierarchies.hpp"

#include "../../utils/finalize.hpp"
#include "../../utils/finalize.cpp"

TEST(UTest4GeneratedTypes, CheckHowGeneratedTypesWork)
{
    using namespace generated_types;

    auto fn = [](std::set<Shape*>& s)
    {
        s.insert(new Triangle(Point{1, 2}, Point{3, 4}, Point{5, 8}));
    };

    auto gc = [&](std::set<Circle*> s)
    {
        // fn(s);  // Error: 类型不匹配错误， s是一个set<Circle*>，而不是一个set<Shape*>
    };

    std::set<Shape*> shapes;
#if true    // If there is no such a deleter, memory leakage definitely occurs.
    auto deleter = finalize([&shapes]() {
        for (Shape* pshape : shapes)
        {
            if (pshape != nullptr)
            {
                delete pshape;
                pshape = nullptr;
            }
        }
    });
#endif

    fn(shapes);
}

TEST(UTest4GeneratedTypes, CheckDisastrousCombinationOfBaseClassAndArray)
{
    using namespace generated_types;

    auto maul = [](Shape* p, int n)
    {
        /*!
         *  \warning    这种基类与数组的结合非常糟糕，因为内置数组并不像容器那样提供类型安全。
         *              像下面的这种写法，看起来无害，但其实非常危险。
         */
        for (int i = 0; i < n; ++i)
        {
            p[i].draw();
        }
    };

    auto user = [&maul]()
    {
        /*!
         *  \warning    我们用image调用maul()会发生什么？
         *              首先，image的类型从Circle[]转换（退化）为Circle*
         *              接下来，Circle*被转换为Shape*
         * 
         *              这种数组名到数组首元素指针的隐式转换是C风格程序设计的基础，
         *              类似地，派生类指针向基类指针的隐式转换是面向对象程序设计的基础。
         *              两者结合，为灾难性后果提供充足的机会。
         */
        Circle image[10];   // 一幅图像由10个圆组成

        maul(image, 10);    // maul画了10个圆
    };

    // user();     /*! \warning    执行就会产生灾难性的Segmentation fault (core dumped)的严重错误，乃至完全崩溃！ */
}