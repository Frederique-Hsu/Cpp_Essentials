/*!
 *  \file       nonintrusive_list.hpp
 *  \brief      
 *  
 */


#pragma once


#define EMBED_CLASS         1
#define FRIEND_CLASS        2
#define ORGANIZE_LIST_BY    FRIEND_CLASS

/*!
 *  \class      List
 *  \brief      Define and implement a non-intrusive list
 * 
 */

#if (ORGANIZE_LIST_BY == EMBED_CLASS)
    template<class T> class List
    {
    public:
        List();
        virtual ~List();

    public:
        void insert(T);
        T get();

    private:
        struct Link
        {
            T       val;
            Link*   next;
        };

        struct Chunk
        {
            enum { chunk_size = 15 };

            Link    v[chunk_size];
            Chunk*  next;
        };

        Chunk* allocated;
        Link* free;
        Link* head;

    private:
        Link* get_free();
    };
#elif (ORGANIZE_LIST_BY == FRIEND_CLASS)
    template<class T> class List;

    template<class T> class Link
    {
        friend class List<T>;

        T       val;
        Link*   next;
    };

    template<class T> class List
    {
    public:
        List();
        virtual ~List();
    private:        /*! \note   对于类的数据成员，不要使用多个访问符来分割它们。因为编译器可能重排它们的顺序，这会影响构造函数的初始化列表顺序。*/
        Link<T>* free;
    // private:
        Link<T>* head;
    public:         /*! \note   而对于成员函数，使用多个访问符分割则无影响，编译器不会重排成员函数列表，也不影响虚函数在vtbl中的索引排列。 */
        void insert(T);
        T get();
    private:
        Link<T>* get_free();
    };
#endif

#include "nonintrusive_list_impl.hpp"

