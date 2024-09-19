/*!
 *  \file       list_impl.hpp
 *  \brief      
 *  
 */


#if defined (NEST_TYPE_DEFINITION_INSIDE_CLASS_TEMPLATE)
    template<typename T, typename Allocator>
    List<T, Allocator>::List() : head{nullptr}
    {
    }
    
    template<typename T, typename Allocator>
    List<T, Allocator>::List(const T& elem) : head{new Link{elem, nullptr, nullptr}}
    {
    }
    
    template<typename T, typename Allocator>
    List<T, Allocator>::~List()
    {
        Link* pnode = head;
        
        while (pnode)
        {
            Link* next_node = pnode->next;
            Link* prev_node = pnode->prev;
            
            delete pnode;
            pnode = next_node;
            pnode->prev = prev_node;
        }
        head = nullptr;
    }
#else
    template<typename T, typename Allocator>
    List<T, Allocator>::List() : head{nullptr}
    {
    }
    
    template<typename T, typename Allocator>
    List<T, Allocator>::List(const T& elem) : head{new Link<T>{elem, nullptr, nullptr}}
    {
    }
    
    template<typename T, typename Allocator>
    List<T, Allocator>::~List()
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
    
    template<typename T, class Allocator>
    Iterator<T> List<T, Allocator>::begin()
    {
        return Iterator<T>{head};
    }
    
    template<typename T, class Allocator>
    Iterator<T> List<T, Allocator>::end()
    {
        Link<T>* pnode = head;
        
        while (pnode)
        {
            pnode = pnode->next;
        }
        return Iterator<T>{pnode};
    }
#endif



