/*!
 *  \file       reference_deduction_impl.hpp
 *  \brief      
 *  
 */


#include "reference_deduction.hpp"

#include <utility>

template<typename T>    // 保存一个指针，Xref是所有者
Xref<T>::Xref(int i, T* ptr) : index{i}, elem{ptr}, owned{true}
{
}

template<typename T>    // 保存一个指向ref的指针，所有者是其他人
Xref<T>::Xref(int i, T& ref) : index{i}, elem{&ref}, owned{false}
{
}

template<typename T>    // 将rvalue_ref移入Xref，Xref变成所有者
Xref<T>::Xref(int i, T&& rvalue_ref) : index{i}, elem{new T{std::move(rvalue_ref)}}, owned{true}
{
}

template<typename T>
Xref<T>::~Xref()
{
    if (owned)
    {
        delete elem;
    }
}

template<typename T, typename A> std::unique_ptr<T> my::make_unique(int i, A&& a)
{
    return std::unique_ptr<T>{new T{i, std::forward<A>(a)}};
}