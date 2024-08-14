/*!
 *  \file       operator_new_delete.cpp
 *  \brief
 *
 */


#include "operator_new_delete.hpp"

#include <iostream>

void* operator new(size_t count)
{
    std::cout << "new(size_t), size = " << count << std::endl;
    if (count == 0)
        ++count;

    if (void* ptr = std::malloc(count))
        return ptr;

    throw std::bad_alloc{};
}

void* operator new[](size_t count)
{
    std::cout << "new[](size_t), size = " << count << std::endl;
    if (count == 0)
        ++count;
    if (void* ptr = std::malloc(count))
        return ptr;
    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept
{
    std::cout << "delete(void*)" << std::endl;
    std::free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept
{
    std::cout << "delete(void*, size_t), size = " << size << std::endl;
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    std::cout << "delete[](void*)" << std::endl;
    std::free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept
{
    std::cout << "delete[](void*, size_t), size = " << size << std::endl;
    std::free(ptr);
}


/*!
 *  \brief      显式new运算符，将对象置于别处
 */
void* X::operator new(size_t count)
{
    std::cout << "Custom operator new for size " <<count << std::endl;
    return ::operator new(count);
}

void* X::operator new[](size_t count)
{
    std::cout << "Custom new[] for size " << count << std::endl;
    return ::operator new[](count);
}

void* X::operator new(size_t, void* ptr)
{
    std::cout << "Placement new(size_t, void*) " << std::endl;
    return ptr;
}
