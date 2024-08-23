/*!
 *  \file       nonintrusive_list_impl.hpp
 *  \brief      
 *  
 */

#if (ORGANIZE_LIST_BY == EMBED_CLASS)
    template<class T>
    void List<T>::insert(T val)
    {
        Link* lnk = get_free();
        lnk->val = val;
        lnk->next = head;
        head = lnk;
    }

    template<class T>
    T List<T>::get()
    {
        if (head == nullptr)
        {
            throw Underflow{};
        }
        Link* p = head;
        head = p->next;
        p->next = free;
        free = p;

        return p->val;
    }

    template<class T>
    typename List<T>::Link* List<T>::get_free()
    {
        if (free == nullptr)
        {
            free = new Link{T{}, nullptr};
            return free;
        }
        Link* p = free;
        free = free->next;
        return p;
    }
#elif (ORGANIZE_LIST_BY == FRIEND_CLASS)
#endif