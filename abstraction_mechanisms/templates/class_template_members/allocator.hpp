/*!
 *  \file       allocator.hpp
 *  \brief      
 *  
 */


#pragma once


template<typename T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    template<class U> struct rebind
    {
        typedef Allocator<U>    other;
    };
public:
    Allocator() noexcept;
    Allocator(const Allocator& other) noexcept;
    template<class U> Allocator(const Allocator<U>& other) noexcept;
    ~Allocator();
public:
    T* allocate(std::size_t n, const void* hint);
    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);
    void construct(pointer p, const_reference val);
    template<class U, typename... Args> void construct(U* p, Args&&... args);
    void destroy(pointer p);
    template<class U> void destroy(U* p);
    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;
    size_type max_size() const noexcept;
};

template<class T1, class T2> bool operator==(const Allocator<T1>& lhs, const Allocator<T2>& rhs) noexcept;
template<class T1, class T2> bool operator!=(const Allocator<T1>& lhs, const Allocator<T2>& rhs) noexcept;

/*================================================================================================*/

template<typename T>
class SimpleAllocator
{
    template<typename U> friend bool operator==(const SimpleAllocator&, const SimpleAllocator<U>&) noexcept
    {
        return true;
    }
    template<typename U> friend bool operator!=(const SimpleAllocator&, const SimpleAllocator<U>&) noexcept
    {
        return false;
    }
public:
    using value_type = T;
public:
    SimpleAllocator();
    template<typename U> constexpr SimpleAllocator(const SimpleAllocator<U>&) noexcept;
    ~SimpleAllocator();
public:
    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t) noexcept;
    template<typename U, typename... Args> void construct(U* p, Args&&... args);
    template<typename U> void destroy(U* p) noexcept;
};



#include "allocator_impl.hpp"