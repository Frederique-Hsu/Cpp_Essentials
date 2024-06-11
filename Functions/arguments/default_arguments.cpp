/*!
 *  \file       default_arguments.cpp
 *  \brief
 *
 */


#include "default_arguments.hpp"

#include <iostream>

namespace my
{
    complex::complex(double real, double imag) : m_real{real}, m_imag{imag}
    {
    }

    /*!
     *  \remark     构造函数重载有很多重复性的工作，处理这种重复性的策略就是认为其中一个构造函数是“真正的那个”，
     *              然后在别的构造函数中使用它。
     */
    complex::complex(double real) : complex(real, 0)
    {
    }

    complex::complex() : complex(0, 0)
    {
    }
}


int X::def_arg = 7;

void X::fn(int)
{
    std::cout << "Current def. argument is " << def_arg << std::endl;
}

void gfn()
{
    void fnct(int x = 9);   // OK: 这个函数声明覆盖外层的fnct(int)函数
}
