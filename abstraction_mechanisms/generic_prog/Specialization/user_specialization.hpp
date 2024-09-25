/*!
 *  \file       user_specialization.hpp
 *  \brief      
 *  
 */


#pragma once


template<typename T>
class Vector        // 通用的主模板
{
private:
    T* elements;
    int sz;
public:
    Vector();
    explicit Vector(int size);
    ~Vector();
public:
    T& at(int i);
    T& operator[](int index);
    
    void swap(Vector&);
    int size() const;
};

template<>
class Vector<void*>     // void*的特例化版本
{
    using VoidPtr = void*;
public:
    Vector() : p{nullptr}, sz{0} {}
    explicit Vector(int i) : p{nullptr}, sz{i}
    {
        p = new VoidPtr[i];
    }
    virtual ~Vector()
    {
        if (p != nullptr)
        {
            delete [] p;
        }
    }
private:
    VoidPtr* p;
    int    sz;
public:
    void*& operator[](int index)
    {
        return p[index];
    }
    void*& at(int i);
    int size() const 
    {
        return sz;
    }
};

template<typename T>
class Vector<T*> : private Vector<void*>    // 任意指针的特例化版本
{
public:
    using Base = Vector<void*>;
    
    Vector() : Base() {}
    explicit Vector(int i) : Base(i)
    {
    }
    ~Vector() = default;
public:
    T*& at(int i);
    T*& operator[](int index);
    int size() const;
};