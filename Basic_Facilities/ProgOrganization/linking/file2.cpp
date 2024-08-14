/*!
 *  \file       file2.cpp
 *  \brief
 *
 */


#include <iostream>
// #include < string >     /*! \warning 在包含指令中，<>或""内的空格不会被忽略。 如果有空格，会导致找不到头文件。 */

#include "common.hpp"

extern int x;

int fn();

void g()
{
    x = fn();
}

/*!
 *  \attention      inline函数在其应用的所有编译单元中都必须是完全等价的定义.
 *
 *  file1.cpp中的fnct(int i)和file2.cpp中的fnct(int i)就是不合法的。
 *
inline int fnct(int i)
{
    return i + 1;
}
 */

extern const int a;

void gn()
{
    std::cout << "\nthe extern const a = " << a << std::endl;
}


/*!
 *  \attention  C++标准中规定类、模板等的定义必须唯一，这一规则是通过一种更为复杂、更为微妙的方式描述的。
 *              它通常被成为单一定义规则 (one-definition rule, ODR)
 *
 *              ODR的设计意图是允许在不同编译单元中包含来自同一个公共源文件的类定义。
 */
