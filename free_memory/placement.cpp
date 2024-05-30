/*!
 *  \file       placement.cpp
 *  \brief
 *
 */


#include "placement.hpp"


X::X(int)
{
}

void* X::operator new(size_t sz, void* p) noexcept     // 将大小为sz的对象置于p处
{
    (void)sz;
    return p;
}

void X::operator delete(void* p, void*) noexcept    // 如果p为真，令*p无效
{
    if (p != nullptr)
    {
        p = nullptr;
    }
}

void* operator new(size_t sz, Arena* a)
{
    return a->alloc(sz);
}
