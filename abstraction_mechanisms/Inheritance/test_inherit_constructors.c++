/*!
 *  \file       test_inherit_constructors.c++
 *  \brief      
 *  
 */


#include "inherit_constructors.hpp"

#include <gtest/gtest.h>

TEST(UTest4Vector, CheckHowToInheritConstructors)
{
    Vector<int> vint{1, 2, 3, 4, 5};

    const int elem2 = vint[1];
    EXPECT_EQ(elem2, 2);

    int elem3 = vint[2];
    EXPECT_EQ(elem3, 3);

    EXPECT_THROW({ int dummy = vint[vint.size()]; }, std::out_of_range);
}

TEST(UTest4InheritConstructors, DerivedClassInheritConstructorButWithNewMember)
{
    struct Parent
    {
        Parent(int)
        {
            std::cout << "Parent(int) constructor" << std::endl;
        }
    };

    struct Child : Parent
    {
        /*!
         *  \attention  继承构造函数等价于只初始化基类的构造函数
         */
        using Parent::Parent;   // implicitly declare the Child(int) constructor

        std::string str;        // std::string has its default constructor
        // int x;                  // but we forget to initialize the x member
        int x{0};               // adding the inside-class initializer for x member can solve this problem
    };

    auto test = []()
    {
        Child sub{6};   // bad:  sub.x had not yet been initialized

        EXPECT_EQ(sub.x, 0);
        // Child child;    // error: Child has no default constructor
    };

    test();
}