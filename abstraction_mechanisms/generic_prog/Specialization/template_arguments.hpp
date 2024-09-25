/*!
 *  \file       template_arguments.hpp
 *  \brief      
 *  
 */


#pragma once


#include <initializer_list>
#include <iostream>
#include <vector>
#include <map>


/*!
 *  \section    Types as arguments
 */


/*!
 *  \section    Values as arguments
 */
template<typename T, int N>
class Buffer
{
public:
    Buffer();
    Buffer(const T array[], int n);
    Buffer(const std::initializer_list<T>& init_list);
    Buffer(const Buffer& rhs);
    Buffer& operator=(const Buffer& rhs);
    Buffer& operator=(const std::initializer_list<T>& init_list);
    Buffer(Buffer&& rhs) = delete;
    Buffer& operator=(Buffer&& rhs) = delete;
    ~Buffer() = default;
private:
    T m_array[N];
public:
    inline const int capacity() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    T* begin();
    const T* cbegin() const;
    T* end();
    const T* cend() const;
};

template<typename T, int N> std::ostream& operator<<(std::ostream& os, const Buffer<T, N>& buf);
template<typename T, int N> std::istream& operator>>(std::istream& is,       Buffer<T, N>& buf);
template<typename T, int M, int N> bool operator==(const Buffer<T, M>& a, const Buffer<T, N>& b);

template<typename T, int N>
using Array = Buffer<T, N>;

/*!
 *  \file   Operations as arguments
 */
namespace my
{
#if false
    template<typename Key, typename Value, bool (*compare)(const Key&, const Key&)>
    class map
    {
    public:
        map();
    private:
        Key m_key;
        Value m_value;
    };
#else
    template<typename Key, typename Value, typename Compare = std::less<Key>>
    class map : public std::map<Key, Value>
    {
    public:
        map();
        explicit map(const Compare& comparator);
    private:
        Compare cmp;
    };
#endif
}

/*!
 *  \file   Templates as arguments
 */

template<typename T, template<typename> class Container>
class Xrefd
{
private:
    Container<T> mems;
    Container<T*> refs;
};

template<typename Container1, typename Container2>
class Xrefd_2Containers
{
private:
    Container1 mems;
    Container2 refs;
};

template<typename T> using MyVec = std::vector<T>;

template<typename T> class MyContainer
{
public:
    MyContainer();
    MyContainer(int size);
    MyContainer(const std::initializer_list<T>& init_list);
    MyContainer(const MyContainer& rhs);
    MyContainer& operator=(const MyContainer& rhs);
    ~MyContainer();
private:
    MyContainer(MyContainer&&);
    MyContainer& operator=(MyContainer&&);
private:
    T* m_elements;
    std::size_t m_size;
};

/*!
 *  \section    Default function template arguments
 */

template<typename Target = std::string, typename Source = std::string> Target to         (Source arg);
template<typename Target,               typename Source              > Target narrow_cast(Source arg);