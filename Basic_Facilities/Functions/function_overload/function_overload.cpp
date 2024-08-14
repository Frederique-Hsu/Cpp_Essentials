/*!
 *  \file       function_overload.cpp
 *  \brief
 *
 */


#include "function_overload.hpp"

void print(int)
{
    std::cout << "called print(int)" << std::endl;
}
void print(const char*)
{
    std::cout << "called print(const char*)" << std::endl;
}
void print(long)
{
    std::cout << "called print(long)" << std::endl;
}
void print(double)
{
    std::cout << "called print(double)" << std::endl;
}
/*
void print(short)
{
    std::cout << "called print(short)" << std::endl;
}
 */
void print(char)
{
    std::cout << "called print(char)" << std::endl;
}


void print_int(int)
{
    std::cout << "called print_int(int)" << std::endl;
}
void print_char(char)
{
    std::cout << "called print_char(char)" << std::endl;
}
void print_string(const char*)
{
    std::cout << "called print_string(const char*)" << std::endl;
}

float sqrt(float f)
{
    std::cout << "called sqrt(float)" << std::endl;
    return f;
}

double sqrt(double d)
{
    std::cout << "called sqrt(double)" << std::endl;
    return d;
}

namespace my
{
int pow(int, int)
{
    std::cout << "called pow(int, int)" << std::endl;
    return int{};
}
double pow(double, double)
{
    std::cout << "called pow(double, double)" << std::endl;
    return double{};
}
}

namespace manual_overload_resultion
{
void f1(char)
{
    std::cout << "called f1(char)" << std::endl;
}
void f1(int n)
{
    f1(long{n});    // 增加一个函数版本解决重载函数过少导致的歧义问题
}
void f1(long)
{
    std::cout << "called f1(long)" << std::endl;
}

void f2(char*)
{
    std::cout << "called f2(char*)" << std::endl;
}
void f2(int*)
{
    std::cout << "called f2(int*)" << std::endl;
}
}

/*!
 *  \brief      计算长方形的面积
 *  \pre        长方形的长和宽都是正数
 *  \post       返回值是正数, 是长方形的面积.
 */
int area(int len, int width)
{
    return len * width;
}
