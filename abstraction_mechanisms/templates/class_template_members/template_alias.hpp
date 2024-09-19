/*!
 *  \file       template_alias.hpp
 *  \brief      
 *  
 */


#pragma once

#include <vector>
#include <string>
#include <sstream>

/* Declaration ===================================================================================*/
template<typename Container>
using Element_Type = typename Container::value_type;

template<typename Container> void algo(Container& container);

template<typename Key, typename Value> class Map;

template<typename Value>
using String_map = Map<std::string, Value>;


template<typename T>
class Vector
{
public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    using reference = T&;
    using const_reference = const value_type&;
    
    Vector(int size = 0);
    Vector(const std::initializer_list<T>& values);
    virtual ~Vector();
private:
    value_type* m_elements;
    std::size_t m_sz;
    std::size_t m_capacity;
public:
    reference operator[](uint index);
    const_reference operator[](uint index) const;
    reference at(uint index);
    const_reference at(uint index) const;
    std::size_t size() const;
    std::size_t capacity() const;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    
    void push_back(const value_type& value);
    void pop_back();
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
};


/* Implementation ================================================================================*/
template<typename Container> void algo(Container& container)
{
    std::vector<Element_Type<Container>> vec;
}

// String_map<int> m;      // m是一个Map<std::string, int>


template<typename T>
Vector<T>::Vector(int size) : m_elements{nullptr}, 
                              m_sz{static_cast<decltype(m_sz)>(size)}, 
                              m_capacity{static_cast<decltype(m_capacity)>(2 * size)}
{
    if (size > 0)
    {
        m_elements = new T[m_capacity];
        if (m_elements == nullptr)
        {
            throw std::bad_alloc();
        }
        
        for (auto index = 0; index < size; ++index)
        {
            *(m_elements + index) = T{};
        }
    }
}

template<typename T>
Vector<T>::~Vector()
{
    if (m_elements != nullptr)
    {
        delete[] m_elements;
    }
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& values) 
    : m_elements{nullptr}, m_sz{values.size()}, m_capacity{2 * m_sz}
{
    if (m_sz > 0)
    {
        m_elements = new T[m_capacity];
        if (m_elements == nullptr)
        {
            throw std::bad_alloc();
        }
        
        for (auto index = 0U; index < m_sz; ++index)
        {
            *(m_elements + index) = *(values.begin() + index);
        }
    }
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](uint index)
{
    if (index >= m_sz)
    {
        std::string error_msg = "The index = ";
        error_msg += std::to_string(index) + " had exceeded the range.";
        throw std::out_of_range(error_msg);
    }
    return *(m_elements + index);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](uint index) const
{
    if (index >= m_sz)
    {
        std::string error_msg = "The index = ";
        error_msg += std::to_string(index) + " had exceeded the range.";
        throw std::out_of_range(error_msg);
    }
    return *(m_elements + index);
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(uint index)
{
    if (index >= m_sz)
    {
        std::string error_msg = "The index = ";
        error_msg += std::to_string(index) + " had exceeded the range.";
        throw std::out_of_range(error_msg);
    }
    return *(m_elements + index);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(uint index) const
{
    if (index >= m_sz)
    {
        std::string error_msg = "The index = ";
        error_msg += std::to_string(index) + " had exceeded the range.";
        throw std::out_of_range(error_msg);
    }
    return *(m_elements + index);
}

template<typename T>
std::size_t Vector<T>::size() const
{
    return m_sz;
}

template<typename T>
std::size_t Vector<T>::capacity() const
{
    return m_capacity;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return m_elements;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return m_elements;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    return m_elements;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return m_elements + m_sz;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return m_elements + m_sz;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept
{
    return m_elements + m_sz;
}

template<typename T>
typename Vector<T>::reference Vector<T>::front()
{
    return *m_elements;
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const
{
    return *m_elements;
}

template<typename T>
typename Vector<T>::reference Vector<T>::back()
{
    return *(m_elements + m_sz - 1);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const
{
    return *(m_elements + m_sz - 1);
}

template<typename T>
void Vector<T>::push_back(const value_type& value)
{
    if (m_sz < m_capacity)
    {
        *(m_elements + m_sz) = value;
        m_sz++;
    }
    else
    {
        m_elements = (T*)std::realloc(m_elements, sizeof(value_type) * (2 * m_capacity));
        *(m_elements + m_sz) = value;
        m_sz++;
        m_capacity *= 2;
    }
}

template<typename T>
void Vector<T>::pop_back()
{
    *(m_elements + m_sz - 1) = T{};
    m_sz--;
}