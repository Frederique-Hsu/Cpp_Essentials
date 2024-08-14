/*!
 *  \file       my.vector.hpp
 *  \brief      标准库vector为我们编写异常安全的代码提供了很好的技术示例。
 *              它的实现覆盖了很多环境和解决方案中都会涉及到的问题。
 *              本子项目即参考std::vector来编写我们自己的异常安全的库。
 *  \author     Frederique Hsu
 *  \date       Thur.   20 June 2024
 *
 */


#pragma once


/*!
 *  \subsection 编写异常安全的代码所需的基本工具包括：
 *
 *  \list
 *      \li     try块
 *      \li     支持“资源获取即初始化”RAII的技术
 *      \li     不要随意丢弃信息，直到我们确认有东西可以替代它为止
 *      \li     在抛出或者重抛出异常时，确保对象处于有效状态。
 *  \endlist
 *
 *              遵循这样的原则，我们就可以确保程序从错误状态中恢复过来。
 *              当你编写标准库文件时，一定要尽量提供强有力的异常安全保障。与之相比，编写特性程序时对异常安全的关注
 *              就会少一些。
 *
 */


#include <memory>

namespace my
{
    template<class T, class A = std::allocator<T>>
    struct vector_base
    {
        A alloc;
        T* elem;
        T* space;
        T* last;

        vector_base(const A& a, typename A::size_type n);
        ~vector_base();

        vector_base(const vector_base&) = delete;
        vector_base& operator=(const vector_base&) = delete;
        vector_base(vector_base&&);
        vector_base& operator=(vector_base&&);
    };

    template<class T, class A = std::allocator<T>>
    class vector
    {
    private:
#if false
        T* elem;
        T* space;
        T* last;
        A alloc;
#else
        vector_base<T, A> vb;
#endif
    public:
        using size_type = unsigned int;

        explicit vector(size_type n, const T& val = T(), const A& = A());
        vector(const vector& a);
        vector& operator=(const vector& a);
        vector(vector&& a);
        vector& operator=(vector&& a);
        ~vector();
    public:
        size_type size() const;
        size_type capacity() const;
        void reserve(size_type n);
        void resize(size_type n, const T& val = {});
        void clear();
        void push_back(const T&);
    private:
        void destroy_elements();
    };

    template<class For, class T>
    void uninitialized_fill(For beg, For end, const T& x);

    template<typename For, typename T>
    T uninitialized_move(For begin, For end, T elem);

    template<class T, class A>
    void safe_assign(vector<T, A>& a, const vector<T, A>& b);

    template<class T, class A>
    void safe_assign(vector<T, A>& a, vector<T, A> b);

    template<class Iter>
    void destroy(Iter begin, Iter end);
}

#include "my.vector.cpp"
