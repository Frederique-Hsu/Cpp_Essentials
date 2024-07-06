/*!
 *  \file       throw_catch_exception.hpp
 *  \brief
 *
 */


#pragma once

/*!
 *  \subsection     抛出异常
 *
 *  \brief          我们可以throw任意类型的异常，前提是它能被拷贝和移动
 */

#include <stdexcept>
#include <vector>
#include <ios>


class NoCopy
{
    NoCopy(const NoCopy&) = delete;
};

class MyError
{
};

struct MyError2 : std::runtime_error
{
    MyError2(const char* err_mesg = "MyError2");

    const char* what() const noexcept;
};

double compute(double) noexcept;

/*!
 *  \remark     可以把函数声明为有条件的noexcept
 *
 *  \details    noexcept(std::is_pod<T>())的含义是：如果谓词is_pod<T>()为true, 则myFnct()不会抛出异常；
 *              反之，如果is_pod<T>()是false, 则myFnct有可能抛出异常。
 *
 *              在noexcept说明中用到的谓词必须是常量表达式 constexpr. 普通的noexcept等价于noexcept(true)
 *
 *              noexcept()运算符接受一条表达式作为它的参数，当编译器“知道”它不能抛出异常时，该运算符返回true,
 *              否则就返回false.
 */
template<typename T> void myFnct(T& x) noexcept(std::is_pod<T>());

template<typename T> void callFn(std::vector<T>& vec) noexcept(noexcept(myFnct(vec[0])));

template<class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));

void g(int) throw();

class Bad : public std::bad_alloc {};

class Worse {};

// void f(int) throw(Bad, Worse);  // Error: C++17 doesn't allow a dynamic exception specification.


class X
{
    std::vector<int> m_vi;
    std::vector<std::string> m_vs;
public:
    X(int, int);
    ~X();
};
