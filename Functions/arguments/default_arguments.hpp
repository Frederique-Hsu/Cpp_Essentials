/*!
 *  \file       default_arguments.hpp
 *  \brief
 *
 */


#pragma once

namespace my
{
    class complex
    {
    public:
        complex(double real = {}, double imag = {});
        explicit complex(double real);
        complex();
    private:
        double m_real;
        double m_imag;
    };
}

class X
{
public:
    static int def_arg;
    void fn(int = def_arg);
};

/*!
 *  \warning    我们只能给参数列表中位置靠后的参数提供默认值
 */
int f(int, int = 0, char* = nullptr);       // OK
// int g(int = 0, int = 0, char*);             // Error
// int h(int = 0, int, char* = nullptr);       // Error

void fnct(int x = 7);
