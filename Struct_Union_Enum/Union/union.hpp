/*!
 *  \file       union.hpp
 *  \brief
 *
 */


#pragma once

#include <complex>

enum Type
{
    str,
    num
};

union Value
{
    char* s;
    int i;
};

struct Entry
{
    char* name;
    Type t;
    Value v;
};

void accessUnion(Entry* p);

/*============================================================================*/

union Fudge
{
    int i;
    int* p;
};

int* cheat(int i);

/*============================================================================*/
/*!
 *  \warning    union的限制：
 *              1. union不能含有虚函数
 *              2. union不能含有引用类型的成员
 *              3. union不能含有基类
 *              4. 如果union的成员含有用户定义的构造函数、拷贝操作、移动操作或者析构函数，则此类函数对于union来说被
 *                 delete掉了。换句话说，union类型的对象不能含有这些函数
 *              5. 在union的所有成员中，最多只能有一个成员包含类内初始化器
 *              6. union不能被用作其他类的基类
 *
 */
union ComplexU
{
    int m1;
    std::complex<double> m2;    // 复数含有构造函数
    std::string m3;     // string含有构造函数
};

union MyUnion
{
    int a;
    const char* p{"MyUnion"};      // C++允许为union的最多一个成员指定类内初始化器
};
