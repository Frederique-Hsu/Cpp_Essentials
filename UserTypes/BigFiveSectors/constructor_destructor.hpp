/*!
 *  \file       constructor_destructor.hpp
 *  \brief
 *
 */


#pragma once

#include <string>


struct Tracer
{
    std::string mess;

    Tracer(const std::string& s);
    ~Tracer();
};

struct Work
{
    std::string author;
    std::string name;
    int year;
};

bool operator==(const Work& a, const Work& b);
bool operator!=(const Work& a, const Work& b);
std::ostream& operator<<(std::ostream& os, const Work& work);

struct Buff
{
    int count;
    unsigned long buff[16];
};

extern int glob;

/*!
 *  \note   引用和const必须被初始化。因此，一个包含这些成员的类不能默认构造，除非程序员提供了类内
 *          成员初始化器，或者定义了一个默认构造函数来初始化他们。
 */
#if false
struct Compound
{
    const int a1{7};
    // const int a2;
    const int& r{9};
    int& r1{glob};
    // int& r2;
};
#endif