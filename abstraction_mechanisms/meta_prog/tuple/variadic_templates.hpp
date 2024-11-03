/*!
 *  \file       variadic_templates.hpp
 *  \brief      
 *  
 */


#pragma once

#include <type_traits>
#include <utility>
#include <iostream>
#include <tuple>


template<typename T, typename... Args> void printf(const char* s, T value, Args... args);

template<typename T> constexpr bool Is_Integral();
template<typename T> constexpr bool Is_Floating_Point();
template<typename T> constexpr bool Is_String();
template<typename T> constexpr bool Is_C_Style_String();

template<typename... Types> void fn(Types... args);

template<typename... Bases>     // 模板实参列表
class X : public Bases...       // 基类说明符列表
{
public:
    X(const Bases&... b)    // 函数实参列表
        : Bases(b)...       // 初始化器列表
    {
    }
};


template<typename... Types>
class PairedTuple
{
public:
    template<typename T, typename U, typename = std::enable_if<sizeof...(Types) == 2>>
    PairedTuple(const std::pair<T, U>&);
private:
};

/*!
 *  \section    Forward 转发
 *              可变参数模板的一个重要用途就是从一个函数向另一个函数转发参数
 */
template<typename FnReturnType, typename... FnArgTypes>
void call(FnReturnType&& fn, FnArgTypes&&... args)
{
    fn(std::forward<FnArgTypes>(args)...);
}

namespace my
{
    template<typename Head, typename... Tail>
    class tuple : private tuple<Tail...>
    {
        using inherited = tuple<Tail...>;
    public:
        constexpr tuple();
        tuple(const Head& vhead, const Tail&... vtail);
        template<typename... ValueTypes> tuple(const tuple<ValueTypes...>& other);
        template<typename... ValueTypes> tuple& operator=(const tuple<ValueTypes...>& other);
    protected:
        Head m_head;
    private:
        // std::add_reference<Head> head();
        // std::add_const_reference<const Head> head() const;
        Head& head();
        const Head& head() const;

        inherited& tail();
        const inherited& tail() const;
    };

    template<typename Head, typename... Tail>
    Head head(tuple<Head, Tail...>& tpl);

    template<typename Head, typename... Tail>
    tuple<Tail&...> tail(tuple<Head, Tail...>& tpl);
}




