/*!
 *  \file       reference_deduction.hpp
 *  \brief      
 *  
 */


#pragma once


#include <type_traits>
#include <memory>

template<typename T>
class Xref
{
public:
    Xref(int i, T* ptr);
    Xref(int i, T& ref);
    Xref(int i, T&& rvalue_ref);
    ~Xref();
private:
    int index;
    T* elem;
    bool owned;
};

namespace my
{
    template<typename T> T&& forward(typename std::remove_reference<T>::type&  t) noexcept;
    template<typename T> T&& forward(typename std::remove_reference<T>::type&& t) noexcept;
    template<typename T, typename A> std::unique_ptr<T> make_unique(int i, A&& a);
}