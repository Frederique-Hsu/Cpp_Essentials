/*!
 *  \file       condition.hpp
 *  \brief      
 *  
 */


#pragma once


#include <type_traits>
#include <iterator>

namespace my
{
    template<bool cond, typename T = void>
    struct enable_if
    {
        using type = T;
    };

    template<typename T>
    struct enable_if<false, T>
    {
    };
}

template<bool cond, typename T>
using Enable_If = typename my::enable_if<cond, T>::type;

template<typename T>
constexpr bool Is_Class()
{
    return std::is_class<T>::value;
}

template<typename T>
class SmartPointer
{
public:
    SmartPointer(T* ptr);
    SmartPointer(const SmartPointer& rhs);
    SmartPointer& operator=(const SmartPointer& rhs);
    virtual ~SmartPointer();
private:
    T* m_ptr;
    unsigned ref_count;
public:
    T& operator*();     // 返回指向整个对象的引用
    Enable_If<Is_Class<T>(), T*> operator->();      // 选择一个成员（仅用于类）
};

template<typename Iter>
constexpr bool Input_Iterator()
{
#if __cplusplus >= 202002L
    return std::input_iterator<Iter>;
#endif
}

namespace my
{
    template<typename T> class Vector
    {
    public:
        Vector(std::size_t, const T& val);
        template<typename Iter, 
                 typename = Enable_If<Input_Iterator<Iter>(), Iter>> 
        Vector(Iter begin, Iter end);
        virtual ~Vector();
    private:
        T* m_elements;
        std::size_t m_size;
    public:
        T* begin();
        T* end();
    };
}