/*!
 *  \file       throw_catch_exception.cpp
 *  \brief
 *
 */


#include "throw_catch_exception.hpp"

#include <vector>
#include <iostream>

MyError2::MyError2(const char* err_mesg) : std::runtime_error(err_mesg)
{
}

const char* MyError2::what() const noexcept
{
    return "MyError2";
}

double compute(double x) noexcept
{
    std::string s = "Courtney and Anya";

    std::vector<double> tmp(10);
}

/*!
 *  \remark     默认情况下，如果基类或成员初始化器抛出了一个异常，则该异常将传递到调用了该成员的类的构造函数的地方。
 *              不过，我们也可以把构造函数的函数体，包括成员初始化器列表在内，放到一个try块中，这样该构造函数就能
 *              自己捕获异常了。 如下：
 */
X::X(int sz1, int sz2)
try
    : m_vi(sz1), m_vs(sz2)
{
    for (int& elem : m_vi)
    {
        elem = 0;
    }
    for (std::string& elem : m_vs)
    {
        elem = std::string();
    }
}
catch (std::exception& err)     // 捕获m_vi和m_vs抛出的异常
{
    std::cerr << "Caught exception: " << err.what() << std::endl;
    throw;
}

X::~X()
{
    try
    {
        // do nothing
    }
    /*!
     *  \note   在析构函数中捕获成员的析构异常，尽管析构函数永远也不会抛出异常。
     */
    catch (...)
    {
        // ...
    }
}

namespace my_exception_handling
{
void m()
{
    try
    {

    }
    catch (std::exception& err)     // handle every standard library exception
    {
        // clean up something...
        throw;
    }
    catch (...)
    {
        // handle any exception
    }
}

void f()
{
    try
    {
        // ....
    }
    catch (std::ios_base::failure)
    {
        // ... 处理各种输入输出错误
    }
    catch (std::exception& err)
    {
        // ... 处理各种标准库异常
    }
    catch (...)
    {
        // ... 处理其他异常
    }
}

void g()
{
    try
    {
        // ...
    }
    catch (std::bad_cast)
    {
        // ...
    }
    catch (std::exception& e)
    {
        // ....
    }
    catch (...)
    {
        // ... 处理各种错误
    }
}
}
