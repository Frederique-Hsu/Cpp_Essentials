/*!
 *  \file       MyFirstVec.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iostream>

template<typename T = double>
class MyFirstVec
{
private:
    int sz;
    T* elements;
public:
    MyFirstVec(int size);
    MyFirstVec(const MyFirstVec<T>& rhs);
    MyFirstVec<T>& operator=(const MyFirstVec<T>& rhs);
    ~MyFirstVec();
public:
    int Size() const;
    T& operator()(int index);
    const T& operator()(int index) const;
    MyFirstVec<T>& operator=(const T& element);
};

template<typename T> MyFirstVec<T> operator+(const MyFirstVec<T>& x, const MyFirstVec<T>& y);
template<typename T> MyFirstVec<T> operator*(double a, const MyFirstVec<T>& x);
template<typename T> std::ostream& operator<<(std::ostream& os, const MyFirstVec<T>& w);