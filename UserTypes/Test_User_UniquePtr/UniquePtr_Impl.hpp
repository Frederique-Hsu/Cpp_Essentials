/*!
 *  \file       UniquePtr_Impl.hpp
 *  \brief
 *
 */


#include <cstdio>

template<typename T>
class UniquePtr
{
    friend std::ostream& operator<<(std::ostream& os, const UniquePtr<T>& ptr)
    {
        if (ptr.m_ptr == nullptr)
        {
            os << "nullptr";
        }
        else
        {
            char output[0xFF];
            std::sprintf(output, "%p", ptr.m_ptr);
            os << output;
        }
        return os;
    }
public:
    explicit UniquePtr(T* ptr);
    virtual ~UniquePtr();
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

private:
    T* m_ptr;

public:
    explicit operator bool() const noexcept;

    T* operator->() const;
    T& operator*() const;
    T* get() const;
};

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr) : m_ptr{ptr}
{
}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
    if (m_ptr != nullptr)
    {
        delete m_ptr;
        m_ptr = nullptr;
    }
}

template<typename T>
UniquePtr<T>::operator bool() const noexcept
{
    return (m_ptr != nullptr);
}

template<typename T>
T* UniquePtr<T>::operator->() const
{
    return m_ptr;
}

template<typename T>
T& UniquePtr<T>::operator*() const
{
    return *m_ptr;
}

template<typename T>
T* UniquePtr<T>::get() const
{
    return m_ptr;
}