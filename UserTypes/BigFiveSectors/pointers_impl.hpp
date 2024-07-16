/*!
 *  \file       pointers_impl.hpp
 *  \brief
 *
 */


#include <cstdio>

namespace pointers
{

template<class T>
CheckedPointer<T>::CheckedPointer(T* ptr) : m_pointer{ptr}
{
    std::printf("called the constructor CheckedPointer<T>::CheckedPointer(ptr = %p).\n", ptr);
}

template<class T>
CheckedPointer<T>::~CheckedPointer()
{
    if (m_pointer)
    {
        // m_pointer->~T();
        delete m_pointer;
        m_pointer = nullptr;

        std::printf("called the destructor CheckedPointer<T>::~CheckedPointer().\n");
    }
}

template<class T>
T& CheckedPointer<T>::operator*()
{
    return *m_pointer;
}

template<class T>
T* CheckedPointer<T>::operator->()
{
    return m_pointer;
}

}
