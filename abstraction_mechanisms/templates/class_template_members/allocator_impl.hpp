/*!
 *  \file       allocator_impl.hpp
 *  \brief      
 *  
 */


#if defined (DEBUG_WITH_LOG)
    #include <iostream>
#endif


template<typename T>
SimpleAllocator<T>::SimpleAllocator()
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called SimpleAllocator<T>::SimpleAllocator() constructor" << std::endl;
#endif
}

template<typename T> template<typename U>
constexpr SimpleAllocator<T>::SimpleAllocator(const SimpleAllocator<U>&) noexcept
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called SimpleAllocator<T>::SimpleAllocator(const SimpleAllocator<U>&) copy constructor" << std::endl;
#endif
}

template<typename T>
SimpleAllocator<T>::~SimpleAllocator()
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called SimpleAllocator<T>::~SimpleAllocator() destructor" << std::endl;
#endif
}

template<typename T>
T* SimpleAllocator<T>::allocate(std::size_t n)
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called T* SimpleAllocator<T>::allocate(std::size_t n)" << std::endl;
#endif

    if (n > std::allocator_traits<SimpleAllocator>::max_size(*this))
    {
        throw std::bad_alloc();
    }
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template<typename T>
void SimpleAllocator<T>::deallocate(T* p, std::size_t) noexcept
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called void SimpleAllocator<T>::deallocate(T* p, std::size_t)" << std::endl;
#endif

    ::operator delete(p);
}

template<typename T> template<typename U, typename... Args>
void SimpleAllocator<T>::construct(U* p, Args&&... args)
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called void SimpleAllocator<T>::construct(U* p, Args&&... args)" << std::endl;
#endif

    new(p) U(std::forward<Args>(args)...);
}

template<typename T> template<typename U>
void SimpleAllocator<T>::destroy(U* p) noexcept
{
#if defined (DEBUG_WITH_LOG)
    std::clog << "called void SimpleAllocator<T>::destroy(U* p)" << std::endl;
#endif

    p->~U();
}