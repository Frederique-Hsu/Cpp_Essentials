/*!
 *  \file       placement.hpp
 *  \brief
 *
 */


#pragma once

#include <cstddef>
#include <new>

/*!
 *  \section    Overload new
 *
 *  \brief      默认情况下，new运算符都是在自由存储（即堆内存上）创建它的对象。
 *              但如果我们想在别的地方分配对象该怎么办？
 */


class X
{
public:
    X(int);

    /* Placement new-delete overload */
    void* operator new(size_t, void* p) noexcept;
    void operator delete(void* p, void*) noexcept;
    void* operator new[](size_t, void* p) noexcept;
    void operator delete[](void* p, void*) noexcept;
};

class Arena
{
public:
    virtual void* alloc(size_t) = 0;
    virtual void free(void*) = 0;

    virtual ~Arena();
};

void* operator new(size_t sz, Arena* a);

/*================================================================================================*/

void* operator new(size_t sz, const std::nothrow_t&) noexcept;
void operator delete(void* p, const std::nothrow_t&) noexcept;
void* operator new[](size_t sz, const std::nothrow_t&) noexcept;
void operator delete[](void* p, const std::nothrow_t&) noexcept;
