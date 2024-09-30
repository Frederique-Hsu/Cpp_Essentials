/*!
 *  \file       MyVector_impl.hpp
 *  \brief      
 *  
 */

#include <stdexcept>

/*!
 *  \section    template implementation
 */
template<typename T>
MyVector<T>::MyVector() : m_elements{nullptr}, m_size{0}
{
}

template<typename T>
MyVector<T>::MyVector(const std::size_t size) : m_elements{new T[size]}, m_size{size}
{
}

template<typename T>
MyVector<T>::~MyVector()
{
    if (m_elements != nullptr)
    {
        delete [] m_elements;
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector& rhs) : m_elements{nullptr}, m_size{rhs.m_size}
{
    m_elements = new T[m_size];
    if (m_elements == nullptr)
    {
        throw std::bad_alloc();
    }
    for (auto index = 0; index < m_size; ++index)
    {
        m_elements[index] = T{};
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs)
{
    if (this != &rhs)
    {
        // firstly destroy the old m_elements pointer
        delete [] m_elements;
        m_elements = nullptr;
        
        m_size = rhs.m_size;
        // then allocate for m_elements pointer with new size
        m_elements = new T[m_size];
        if (m_elements == nullptr)
        {
            throw std::bad_alloc();
        }
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& rhs) : m_size{rhs.m_size}
{
    m_elements = rhs.m_elements;
    
    rhs.m_elements = nullptr;
    rhs.m_size = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& rhs)
{
    if (this != &rhs)
    {
        delete [] m_elements;
        m_elements = nullptr;
        
        m_size = rhs.m_size;
        
        rhs.m_size = 0;
        rhs.m_elements = nullptr;
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(const std::initializer_list<T>& init_list) : m_size{init_list.size()}
{
    m_elements = new T[m_size];
    
    int index = 0;
    for (T elem : init_list)
    {
        *(m_elements + (index++)) = elem;
    }
}

template<typename T>
T& MyVector<T>::operator[](int index)
{
    // std::cout << "called the primary template edition:  T& MyVector<T>::operator[](int index)" << std::endl;
    return *(m_elements + index);
}

template<typename T>
const T& MyVector<T>::operator[](int index) const
{
    // std::cout << "called the primary template edition:  const T& MyVector<T>::operator[](int index) const" << std::endl;
    return *(m_elements + index);
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin()
{
    return m_elements;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::end()
{
    return m_elements + m_size;
}

template<typename T>
std::size_t MyVector<T>::size() const
{
    return m_size;
}