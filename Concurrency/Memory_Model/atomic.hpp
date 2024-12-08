/*!
 *  \file       atomic.hpp
 *  \brief
 *
 */



#pragma once


#include <atomic>
#include <memory>

namespace myspace
{
template<typename T>
class shared_ptr
{
public:
    shared_ptr(T* ptr);
    ~shared_ptr();
private:
    T* p;
    std::atomic<int>* puc;      /* 指向使用计数的指针 */
};
}


#include "atomic_impl.hpp"
