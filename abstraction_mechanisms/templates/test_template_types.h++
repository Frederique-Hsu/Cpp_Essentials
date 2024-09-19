/*!
 *  \file       test_template_types.h++
 *  \brief      
 *  
 */


#pragma once


template<typename T>
struct Link
{
    Link*   prev;
    Link*   next;
    T       val;
};


template<typename T>
class List
{
private:
    Link<T>* head;
public:
    List();
    List(const T& t);
    ~List();
public:
    void traverse(void (*access)(T& elem)) const;
private:
    void destroy();
};

template<typename T>
List<T>::List() : head{nullptr}
{
}

template<typename T>
List<T>::~List()
{
    if (head != nullptr)
    {
        destroy();
    }
}

template<typename T>
void List<T>::destroy()
{
    Link<T>* pnode = head;
    
    while (pnode)
    {
        Link<T>* next_node = pnode->next;
        Link<T>* prev_node = pnode->prev;
        
        delete pnode;
        pnode = next_node;
        pnode->prev = prev_node;
    }
    head = nullptr;
}

template<typename T>
List<T>::List(const T& t) : head(new Link<T>{nullptr, nullptr, t})
{
}

template<typename T>
void List<T>::traverse(void (*access)(T& elem)) const
{
    Link<T>* pnode = head;
    
    while (pnode)
    {
        access(pnode->val);
        pnode = pnode->next;
    }
}