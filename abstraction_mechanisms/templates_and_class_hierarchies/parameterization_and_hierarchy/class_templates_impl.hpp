/*!
 *  \file       class_templates_impl.hpp
 *  \brief      
 *  
 */


template<typename T>
Ptr<T>::Ptr(T* p) : ptr{p}, ref_count{0}
{
    ref_count++;
}

template<typename T>
Ptr<T>::Ptr(const Ptr& rhs) : ptr{rhs.ptr}, ref_count{rhs.ref_count}
{
    ref_count++;
}

template<typename T>
Ptr<T>::~Ptr()
{
    if (--ref_count == 0)
    {
        if (ptr != nullptr)
        {
            delete ptr;
        }
    }
}

template<typename T> template<typename T2>
Ptr<T>::operator Ptr<T2>()
{
    ref_count--;
    return Ptr<T2>{dynamic_cast<T2*>(ptr)};
}

template<typename T>
T& Ptr<T>::operator*()
{
    return *ptr;
}

template<typename T>
T* Ptr<T>::operator->()
{
    return ptr;
}
