/*!
 *  \file       template_arguments.cpp
 *  \brief      
 *  
 */


#include "template_arguments.hpp"

#include <cstring>
#include <cctype>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>

template<typename T, int N>
Buffer<T, N>::Buffer()
{
    for (int index = 0; index < N; ++index)
    {
        m_array[index] = T{};
    }
}

template<typename T, int N>
inline const int Buffer<T, N>::capacity() const
{
    return N;
}

template<typename T, int N>
T& Buffer<T, N>::operator[](int index)
{
    if ((index < 0) or (index >= N))
    {
        std::string error_msg = "The index = ";
        error_msg += std::to_string(index) + " had exceeded the range [0, " + std::to_string(N) + ").";
        throw std::out_of_range(error_msg.c_str());
    }
    
    return m_array[index];
}

template<typename T, int N>
Buffer<T, N>::Buffer(const T array[], int n) : m_array{T{}}
{
    if (n < 0 or n > N)
    {
        throw std::out_of_range("The n had exceeded the array range.");
    }
    
    for (int index = 0; index < n; ++index)
    {
        m_array[index] = array[index];
    }
}

template<typename T, int N>
Buffer<T, N>::Buffer(const std::initializer_list<T>& init_list) : m_array{T{}}
{
    auto size = init_list.size();
    if (size > N)
    {
        std::string error_msg = "The list's size = ";
        error_msg += std::to_string(size) + " had exceeded the array range [0, " + std::to_string(N) + ").";
        throw std::out_of_range(error_msg.c_str());
    }
    
    int index = 0;
    for (auto value : init_list)
    {
        m_array[index++] = value;
    }
}

template<typename T, int N>
Buffer<T, N>& Buffer<T, N>::operator=(const std::initializer_list<T>& init_list)
{
    auto size = init_list.size();
    if (size > N)
    {
        std::string error_msg = "The list's size = ";
        error_msg += std::to_string(size) + " had exceeded the array range [0, " + std::to_string(N) + ").";
        throw std::out_of_range(error_msg.c_str());
    }
    
    std::memset(m_array, 0x00, sizeof(T) * N);
    int index = 0;
    for (auto value : init_list)
    {
        m_array[index++] = value;
    }
    return *this;
}

template<typename T, int N>
const T& Buffer<T, N>::operator[](int index) const
{
#if false
    /*!
     *  \warning    cannot write like the below code
     *              it will fail in compilation, because of infinite recursive invokation.
     */
    return operator[](index);
#else
    if ((index < 0) or (index >= N))
    {
        std::string error_msg = "The index = ";
        error_msg += std::to_string(index) + " had exceeded the range [0, " + std::to_string(N) + ").";
        throw std::out_of_range(error_msg.c_str());
    }
    return m_array[index];
#endif
}

template<typename T, int N>
inline T* Buffer<T, N>::begin()
{
    return m_array;
}

template<typename T, int N>
inline T* Buffer<T, N>::end()
{
    return m_array + N;
}

template<typename T, int N>
inline const T* Buffer<T, N>::cbegin() const
{
    return m_array;
}

template<typename T, int N>
inline const T* Buffer<T, N>::cend() const
{
    return m_array + N;
}

template<typename T, int N>
Buffer<T, N>::Buffer(const Buffer& rhs) : m_array{T{}}
{
    if (N < rhs.capacity())
    {
        std::string error_msg = "rhs's array length = ";
        error_msg += std::to_string(rhs.capacity()) + " had exceeded the Buffer<T, N = " +
                     std::to_string(N) + "> array max length.";
        throw std::length_error(error_msg.c_str());
    }
    
    std::copy(rhs.m_array, rhs.m_array + rhs.capacity(), m_array);
}

template<typename T, int N>
Buffer<T, N>& Buffer<T, N>::operator=(const Buffer& rhs)
{
    if (N < rhs.capacity())
    {
        std::string error_msg = "rhs's array length = ";
        error_msg += std::to_string(rhs.capacity()) + " had exceeded the Buffer<T, N = " +
                     std::to_string(N) + "> array max length.";
        throw std::length_error(error_msg.c_str());
    }
    
    if (this != &rhs)
    {
        std::memset(m_array, 0x00, sizeof(T) * N);
        std::copy(rhs.m_array, rhs.m_array + rhs.capacity(), m_array);
    }
    return *this;
}

template<typename T, int M, int N> 
bool operator==(const Buffer<T, M>& a, const Buffer<T, N>& b)
{
    if (M != N)
    {
        return false;
    }
    for (auto index = 0; index < N; ++index)
    {
        if (a[index] != b[index])
        {
            return false;
        }
    }
    return true;
}

template<typename T, int N> 
std::ostream& operator<<(std::ostream& os, const Buffer<T, N>& buf)
{
    for (auto index = 0; index < N; ++index)
    {
        os << buf[index] << ",  ";
    }
    return os;
}

template<typename T, int N> std::istream& operator>>(std::istream& is, Buffer<T, N>& buf)
{
    int index = 0;
    while (is >> buf[index++])
    {
        if (index >= N)
        {
            break;
        }
    }
    return is;
}

template<typename Key, typename Value, typename Compare>
my::map<Key, Value, Compare>::map() : cmp{}
{
}

template<typename Key, typename Value, typename Compare>
my::map<Key, Value, Compare>::map(const Compare& comparator) : std::map<Key, Value>(comparator), cmp{comparator}
{
}

template<typename T>
MyContainer<T>::MyContainer() : m_elements{nullptr}, m_size{0}
{
}

template<typename T>
MyContainer<T>::MyContainer(int size) : m_elements{new T[size]}, m_size{static_cast<std::size_t>(size)}
{
    for (T* element : m_elements)
    {
        *element = T{};
    }
}

template<typename T>
MyContainer<T>::~MyContainer()
{
    if (m_elements != nullptr)
    {
        delete [] m_elements;
    }
}

template<typename T>
MyContainer<T>::MyContainer(const std::initializer_list<T>& init_list) : m_elements{nullptr}, m_size{init_list.size()}
{
    m_elements = new T[m_size];
    
    int index = 0;
    for (auto& element : init_list)
    {
        m_elements[index++] = element;
    }
}

template<typename T>
MyContainer<T>::MyContainer(const MyContainer& rhs) : m_elements{nullptr}, m_size{rhs.m_size}
{
    m_elements = new T[m_size];
    for (int index = 0; index < m_size; ++index)
    {
        m_elements[index] = rhs.m_elements[index];
    }
}

template<typename T>
MyContainer<T>& MyContainer<T>::operator=(const MyContainer& rhs)
{
    if (this != &rhs)
    {
        delete [] m_elements;
        
        m_size = rhs.m_size;
        m_elements = new T[rhs.m_size];
        for (int index = 0; index < m_size; ++index)
        {
            m_elements[index] = rhs.m_elements[index];
        }
    }
    return *this;
}

template<typename Target, typename Source>
Target to(Source arg)
{
    std::stringstream interpreter;
    Target result;
    
    if (!(interpreter << arg) or            // write arg into the stream
        !(interpreter >> result) or         // read result from stream
        !(interpreter >> std::ws).eof())    // stuff left in the stream
    {
        throw std::runtime_error("to() failed");
    }
    return result;
}

template<typename Target, typename Source>
Target narrow_cast(Source arg)
{
    auto result = static_cast<Target>(arg);     // convert the value type arg. to the target type
    if (static_cast<Source>(result) != arg)
    {
        throw std::runtime_error("narrow_cast<> failed.");
    }
    return result;
}