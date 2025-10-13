/*!
 *  \file       background_task.hpp
 *  \brief
 *
 */


#pragma once


/*!
 *  \class  background_task
 *  \brief  std::thread 可以用防函数类型来构造，将带有函数调用符类型的实例传入 std::thread 类中，替换默认的构造函数。
 *
 */
class BackgroundTask
{
public:
    void operator()() const;
};


void doSomething();
void doSomethingElse();
