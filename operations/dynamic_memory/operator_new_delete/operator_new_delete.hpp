/*!
 *  \file       operator_new_delete.hpp
 *  \brief
 *
 */


#pragma once

#include <cstddef>
#include <new>

void* operator new(size_t count);
void  operator delete(void* ptr) noexcept;
void  operator delete(void* ptr, size_t size) noexcept;
void* operator new[](size_t count);
void  operator delete[](void* ptr) noexcept;
void  operator delete[](void* ptr, size_t size) noexcept;

void* operator new(size_t sz, const std::nothrow_t&) noexcept;
void  operator delete(void* p, const std::nothrow_t&) noexcept;
void* operator new[](size_t sz, const std::nothrow_t&) noexcept;
void  operator delete[](void* p, const std::nothrow_t&) noexcept;

class X
{
public:
    static void* operator new(size_t count);
    static void* operator new[](size_t count);

    void* operator new(size_t, void* ptr);
};

class Arena
{
public:
    virtual void* alloc(size_t) = 0;
    virtual void free(void*) = 0;
};

#if 0
void* operator new(size_t sz, Arena* a)
{
    return a->alloc(sz);
}

void operator delete(void* ptr, Arena* a)
{
    a->free(ptr);
}
#endif
