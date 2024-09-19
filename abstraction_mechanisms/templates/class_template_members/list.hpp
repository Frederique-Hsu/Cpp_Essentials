/*!
 *  \file       list.hpp
 *  \brief      
 *  
 */


#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>


#if defined (NEST_TYPE_DEFINITION_INSIDE_CLASS_TEMPLATE)
    template<typename T, typename Allocator = std::allocator<T>>
    class List
    {
    public:
        using size_type = std::size_t;
        using value_type = T;
        using allocator_type = Allocator;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using pointer = typename Allocator::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    private:
        struct Link
        {
            T       val;
            Link*   prev;
            Link*   next;
        };
    public:
        List();
        List(const T& elem);
        
        explicit List(const Allocator& alloc);
        List(size_type count, const T& value, const Allocator& alloc = Allocator());
        explicit List(size_type count, const Allocator& alloc = Allocator());
        template<class InputIter> List(InputIter first, InputIter last, const Allocator& alloc = Allocator());
        List(const List& other);
        List(const List& other, const Allocator& alloc);
        List(List&& other);
        List(List&& other, const Allocator& alloc);
        List(std::initializer_list<T> init, const Allocator& alloc = Allocator());
        List& operator=(const List& other);
        List& operator=(List&& other) noexcept;
        List& operator=(std::initializer_list<value_type> ilist);
        
        ~List();
    private:
        Link* head;
    public:
        void assign(size_type count, const T& value);
        template<class InputIter> void assign(InputIter first, InputIter last);
        void assign(std::initializer_list<T> ilist);
        allocator_type get_allocator() const;
        size_type size() const noexcept;
        size_type max_size() const;
        void resize(size_type count);
        void resize(size_type count, const value_type& value);
        bool empty() const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
        void push_back(const T& value);
        void push_back(T&& value);
        void push_front(const T& value);
        void push_front(T&& value);
        void pop_front();
        void pop_back();
        void clear();
        iterator erase(iterator pos);
        iterator erase(const_iterator pos);
        iterator erase(iterator first, iterator last);
        iterator erase(const_iterator first, const_iterator last);
        iterator insert(const_iterator pos, const T& value);
        iterator insert(const_iterator pos, T&& value);
        iterator insert(const_iterator pos, size_type count, const T& value);
        template<class InputIterator> iterator insert(const_iterator pos, InputIterator first, InputIterator last);
        iterator insert(const_iterator pos, std::initializer_list<T> ilist);
        template<typename... Args> iterator emplace(const_iterator pos, Args&&... args);
        template<typename... Args> void emplace_front(Args&&... args);
        template<typename... Args> reference emplace_front(Args&... args);
        template<typename... Args> void emplace_back(Args&&... args);
        template<typename... Args> reference emplace_back(Args&... args);
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const noexcept;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        const_reverse_iterator crend() const noexcept;
        void swap(List& other) noexcept;
        void merge(List& other);
        void merge(List&& other);
        template<class Compare> void merge(List& other, Compare compare);
        template<class Compare> void merge(List&& other, Compare compare);
        void splice(const_iterator pos, List& other);
        void splice(const_iterator pos, List&& other);
        void splice(const_iterator pos, List& other, const_iterator it);
        void splice(const_iterator pos, List&& other, const_iterator it);
        void splice(const_iterator pos, List& other, const_iterator first, const_iterator last);
        void splice(const_iterator pos, List&& other, const_iterator first, const_iterator last);
        size_type remove(const T& value);
        template<class UnaryPredicate> size_type remove_if(UnaryPredicate pred);
        void reverse();
        void unique();
        template<class BinaryPredicate> void unique(BinaryPredicate pred);
        void sort();
        template<class Comparator> void sort(Comparator comp);
    };
    
    template<typename T, class Alloc> bool operator==(const List<T, Alloc>& lhs, const List<T, Alloc>& rhs);
    template<typename T, class Alloc> bool operator!=(const List<T, Alloc>& lhs, const List<T, Alloc>& rhs);
    template<typename T, class Alloc> bool operator< (const List<T, Alloc>& lhs, const List<T, Alloc>& rhs);
    template<typename T, class Alloc> bool operator<=(const List<T, Alloc>& lhs, const List<T, Alloc>& rhs);
    template<typename T, class Alloc> bool operator> (const List<T, Alloc>& lhs, const List<T, Alloc>& rhs);
    template<typename T, class Alloc> bool operator>=(const List<T, Alloc>& lhs, const List<T, Alloc>& rhs);
    
    template<typename T, class Alloc> void swap(List<T, Alloc>& lhs, List<T, Alloc>& rhs) noexcept;
    template<typename T, class Alloc, class U> typename List<T, Alloc>::size_type erase(List<T, Alloc>& list, const U& value);
    template<typename T, class Alloc, class Predicate> typename List<T, Alloc>::size_type erase_if(List<T, Alloc>& list, Predicate pred);
#else
    template<typename T, typename Allocator = std::allocator<T>> class List;
    
    template<typename T> class Link
    {
        template<typename U, typename Allocator> friend class List;
        
        T       val;
        Link*   prev;
        Link*   next;
    };
    
    template<typename T> struct Iterator
    {
        Link<T>* current_position;
    };
    
    template<typename T, typename Allocator> class List
    {
    public:
        List();
        List(const T& elem);
        ~List();
    private:
        Link<T>* head;
    public:
        Iterator<T> begin();
        Iterator<T> end();
    };
#endif


#include "list_impl.hpp"

