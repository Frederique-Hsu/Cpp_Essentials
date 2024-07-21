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


template<typename T>
pointers::Handler<T>::Handler(T* ptr) : m_handler{ptr}
{
}

template<typename T>
pointers::Handler<T>::~Handler()
{
    if (m_handler)
    {
        delete m_handler;
    }
}

template<typename T>
pointers::Handler<T>::Handler(const Handler<T>& rhs) : m_handler{new T{*rhs.m_handler}}
{
}

template<typename T>
pointers::Handler<T>& pointers::Handler<T>::operator=(const Handler<T>& rhs)
{
    if (this != &rhs)
    {
        m_handler = new T{*rhs.m_handler};
    }
    return *this;
}

template<typename T>
pointers::Handler<T>::Handler(Handler<T>&& rhs)
{
    m_handler = new T{*rhs.m_handler};

    delete rhs.m_handler;
    rhs.m_handler = nullptr;
}

template<typename T>
pointers::Handler<T>& pointers::Handler<T>::operator=(Handler<T>&& rhs)
{
    if (this != &rhs)
    {
        m_handler = new T{*rhs.m_handler};

        delete rhs.m_handler;
        rhs.m_handler = nullptr;
    }
    return *this;
}

template<typename T>
T& pointers::Handler<T>::operator*()
{
    return *m_handler;
}

template<typename T>
T* pointers::Handler<T>::operator->()
{
    return m_handler;
}

template<typename T>
T* pointers::Handler<T>::get() const
{
    return m_handler;
}