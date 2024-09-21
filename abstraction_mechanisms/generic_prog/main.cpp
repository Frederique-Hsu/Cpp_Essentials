/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <catch2/catch_session.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    return Catch::Session().run(argc, argv);
}


/*!
 *  \section    泛型程序设计
 *  \brief      在C++语境中，”泛型程序设计“强调用模板实现通用算法的设计。
 * 
 *              而更多地关注代码生成技术（将模板看作类型和函数的生成器），并以来类型函数表示编译时计算的编程
 *              方式被称为模板元程序设计 template meta programming
 * 
 *  \list       泛型程序设计的两个重要方面：
 * 
 *      \li     提升：
 *              泛化一个算法，使之能适用最大（但合理）范围的实参类型。即，限制一个算法（或一个类）只依赖必要的属性
 * 
 *      \li     概念：
 *              周密且严谨地说明一个算法（或一个类）对其实参的要求。
 *  \endlist
 *  
 */