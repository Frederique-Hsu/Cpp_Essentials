/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \note       显式类型转换
 *
 *              有时候，我们必须把一种类型的值转换成另一种类型的值，很多这种类型的转换都是根据语言的规则隐式执行的。
 *              但在另外一些情况下，必须显式地转换类型.
 *
 *  \list       C++提供了多种显式类型转换的操作，这些操作在便利程度和安全性上都有所不同：
 *
 *  \li         构造， 使用{}符号提供对新值类型安全的构造
 *
 *  \li         命名的转换，提供不同等级的类型转换：
 *
 *              \list
 *              \li         const_cast          对某些声明为const的对象获得写入的权限
 *              \li         static_cast         反转一个定义良好的隐式类型转换
 *              \li         reinterpret_cast    改变位模式的含义
 *              \li         dynamic_cast        动态地检查类层次关系
 *              \endlist
 *
 *  \li         C风格的转换，提供命名的类型转换或其组合
 *
 *  \li         函数化符号，提供C风格转换的另一种形式
 *
 *  \endlist
 */
