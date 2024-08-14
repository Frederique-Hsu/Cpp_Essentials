/*!
 *  \file       my.vector.cpp
 *  \brief      Implement the my::vector<> template
 *
 */


#define INITIALIZE_BY_NATIVE                1
#define INITIALIZE_BY_UNINITIALIZED_FILL    2
#define INITIALIZED_BY                      INITIALIZE_BY_UNINITIALIZED_FILL

namespace my
{
template<class T, class A>
vector_base<T, A>::vector_base(const A& a, typename A::size_type n)
    : alloc{a}, elem{alloc.allocate(n)}, space{elem + n}, last{elem + n}
{
}

template<class T, class A>
vector_base<T, A>::~vector_base()
{
    alloc.deallocate(elem, last - elem);
}

template<class T, class A>
vector_base<T, A>::vector_base(vector_base&& rhs)
    : alloc{rhs.alloc}, elem{rhs.elem}, space{rhs.space}, last{rhs.last}
{
    rhs.elem = rhs.space = rhs.last = nullptr;
}

template<class T, class A>
vector_base<T, A>& vector_base<T, A>::operator=(vector_base&& rhs)
{
    std::swap(*this, rhs);
    return *this;
}

#if false
    template<class T, class A>
    vector<T, A>::vector(size_type n, const T& val, const A& a) : alloc(a)  // 拷贝分配器
    {
#if (INITIALIZED_BY == INITIALIZE_BY_NATIVE)
        elem = alloc.allocate(n);   // 分配元素的空间

        using iterator = T*;
        iterator p;

        try
        {
            iterator end = elem + n;
            for (p = elem; p != end; ++p)
            {
                alloc.construct(p, val);    // 构造元素
            }
            last = space = p;
        }
        catch (...)
        {
            for (iterator q = elem; q != p; ++q)
            {
                alloc.destroy(q);           // 销毁已构造的元素
            }
            alloc.deallocate(elem, n);      // 释放内存
            throw;                          // 重新抛出
        }
#elif (INITIALIZED_BY == INITIALIZE_BY_UNINITIALIZED_FILL)
        elem = alloc.allocate(n);

        try
        {
            uninitialized_fill(elem, elem + n, val);
            space = last = elem + n;
        }
        catch (...)
        {
            alloc.deallocate(elem, n);
            throw;
        }
#endif
    }
#else
    template<class T, class A>
    vector<T, A>::vector(size_type n, const T& val, const A& a) : vb(a, n)
    {
        uninitialized_fill(vb.elem, vb.elem + n, val);
    }
#endif

template<class T, class A>
vector<T, A>::~vector()
{
    destroy_elements();
}

template<class T, class A>
void vector<T, A>::destroy_elements()
{
    for (T* p = vb.elem; p != vb.last; ++p)
    {
        p->~T();
    }
    vb.space = vb.elem;
}

template<class T, class A>
vector<T, A>::vector(const vector<T, A>& rhs) : vb(rhs.vb.alloc, rhs.size())
{
    std::uninitialized_copy(rhs.vb.elem, rhs.vb.last, rhs.vb.elem);
}

template<class T, class A>
vector<T, A>::vector(vector&& rhs) : vb(std::move(rhs.vb))
{
}

template<class T, class A>
vector<T, A>& vector<T, A>::operator=(vector&& rhs)
{
    clear();
    std::swap(*this, rhs);
    return *this;
}

template<class T, class A>
vector<T, A>& vector<T, A>::operator=(const vector& rhs)
{
    if (capacity() < rhs.size())
    {
        vector temp(rhs);
        std::swap(*this, temp);
        return *this;
    }
    if (this == &rhs)
    {
        return *this;
    }

    size_type sz = size();
    size_type rhs_size = rhs.size();
    vb.alloc = rhs.vb.alloc;

    if (rhs_size <= sz)
    {
        std::copy(rhs.vb.elem, rhs.vb.elem + rhs_size, vb.elem);
        for (T* p = vb.elem + rhs_size; p != vb.space; ++p)     // 销毁多余的元素
        {
            p->~T();
        }
    }
    else
    {
        std::copy(rhs.vb.elem, rhs.vb.elem + sz, vb.elem);
        std::uninitialized_copy(rhs.vb.elem + sz, rhs.vb.last, vb.space);   // 构建额外的元素
    }
    vb.space = vb.elem + rhs_size;
    return *this;
}

template<class T, class A>
void vector<T, A>::clear()
{
    resize(0);
}

template<class T, class A>
typename vector<T, A>::size_type vector<T, A>::size() const
{
    return vb.space - vb.elem;
}

template<class T, class A>
typename vector<T, A>::size_type vector<T, A>::capacity() const
{
    return vb.last - vb.elem;
}

template<class T, class A>
void vector<T, A>::reserve(size_type n)
{
    if (n <= capacity())
    {
        return;
    }
    vector_base<T, A> b(vb.alloc, n);
    std::uninitialized_move(vb.elem, vb.elem + size(), vb.elem);
    std::swap(vb, b);
}

template<class T, class A>
void vector<T, A>::resize(size_type n, const T& val)
{
    reserve(n);
    if (size() < n)
    {
        uninitialized_fill(vb.elem + size(), vb.elem + n, val);
    }
    else
    {
        destroy(vb.elem + size(), vb.elem + n);
    }
    vb.space = vb.last = vb.elem + n;
}

template<class T, class A>
void vector<T, A>::push_back(const T& x)
{
    auto sz = size();
    if (capacity() == sz)
    {
        reserve(sz ? 2 * sz : 8);
    }
    vb.alloc.construct(vb.elems[sz], x);
    ++vb.space;
}

template<class For, class T>
void uninitialized_fill(For beg, For end, const T& x)
{
    For p;
    try
    {
        for (p = beg; p != end; ++p)
        {
            ::new(static_cast<void*>(&*p)) T(x);    // 在*p中构造x的拷贝
        }
    }
    catch (...)
    {
        for (For q = beg; q != p; ++q)
        {
            (&*q)->~T();        // 销毁元素
        }
        throw;                  // 重新抛出
    }
}

template<typename For, typename Iter>
Iter uninitialized_move(For begin, For end, Iter it)
{
    using T = typename std::iterator_traits<Iter>::value_type;
    Iter current = it;
    for (; begin != end; ++begin, ++current)
    {
        new (static_cast<void*>(&*current)) T{std::move(*begin)};
        begin->~T();
    }
    return current;
}

template<class T, class A>
void safe_assign(vector<T, A>& a, const vector<T, A>& b)
{
    vector<T, A> temp(b);
    std::swap(a, temp);
}

template<class T, class A>
void safe_assign(vector<T, A>& a, vector<T, A> b)
{
    std::swap(a, b);
}

template<class Iter>
void destroy(Iter begin, Iter end)
{
    using T = typename std::iterator_traits<Iter>::value_type;
    for (; begin != end; ++begin)
    {
        begin->~T();
    }
}
}
