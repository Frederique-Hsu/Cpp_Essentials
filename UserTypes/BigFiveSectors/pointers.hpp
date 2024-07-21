/*!
 *  \file       pointers.hpp
 *  \brief
 *
 */


#pragma once


namespace pointers
{

template<class T>
class CheckedPointer
{
public:
    CheckedPointer(T* ptr = new T{});
    ~CheckedPointer();

    /*!
     *  \warning    如果一个类有指针成员，就要对编译器生成的拷贝和移动操作保持警惕。
     *              如果该指针成员表示所有权，逐成员拷贝就是错误的。
     *              如果该指针成员不表示所有权，逐个成员拷贝是恰当的。
     *              需要采用显式 = delete 删除编译器生成的拷贝与移动操作。如下：
     */
    CheckedPointer(const CheckedPointer<T>&) = delete;
    CheckedPointer<T>& operator=(const CheckedPointer<T>&) = delete;

private:
    T* m_pointer;

public:
    T& operator*();
    T* operator->();
};


template<typename T>
class Handler
{
public:
    Handler(T* ptr);
    Handler(const Handler<T>& rhs);
    Handler<T>& operator=(const Handler<T>& rhs);
    Handler(Handler<T>&& rhs);
    Handler<T>& operator=(Handler<T>&& rhs);
    ~Handler();

private:
    T* m_handler;

public:
    T& operator*();
    T* operator->();
    T* get() const;
};

}   // namespace pointers


#include "pointers_impl.hpp"

