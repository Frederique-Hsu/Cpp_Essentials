/*!
 *  \file       pointers.hpp
 *  \brief
 *
 */


#pragma once


namespace pointers
{

template<class T>
class CheckedPointer
{
public:
    CheckedPointer(T* ptr = new T{});
    ~CheckedPointer();

private:
    T* m_pointer;

public:
    T& operator*();
    T* operator->();
};

}   // namespace pointers


#include "pointers_impl.hpp"
