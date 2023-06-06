/*!
 *  \file       pod.hpp
 *  \brief      
 *  
 */



#pragma once

struct S0       // 是POD
{
};

struct S1       // 是POD
{
    int a;
};

struct S2       // 不是POD, 不是默认构造函数
{
    int a;
    S2(int aa) : a(aa) {}
};

struct S3       // 不是POD, 用户自定义的默认构造函数
{
    int a;
    S3(int aa) : a(aa) {}
    S3() {}
};

struct S4       // 是POD
{
    int a;
    S4(int aa) : a(aa) {}
    S4() = default;
};

struct S5       // 不是POD，含有一个虚函数
{
    virtual void f();
};

struct S6 : S1  // 是POD
{
};

struct S7 : S0  // 是POD
{
    int b;
};

struct S8 : S1  // 不是POD, 数据既属于S1, 也属于S8
{
    int b;
};

struct S9 : S0, S1  // 是POD
{
};

/*============================================================================*/

#include <type_traits>
#include <cstring>

template<typename T>
void mycopy(T* to, const T* from, int count)
{
    if (std::is_pod<T>::value)
    {
        std::memcpy(to, from, count * sizeof(T));
    }
    else
    {
        for (int i = 0; i != count; ++i)
        {
            to[i] = from[i];
        }
    }
}