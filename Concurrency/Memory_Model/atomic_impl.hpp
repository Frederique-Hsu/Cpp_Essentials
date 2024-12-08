/*!
 *  \file       atomic_impl.hpp
 *  \brief
 *
 */


namespace myspace
{
template<typename T> shared_ptr<T>::shared_ptr(T* ptr) : p{ptr}, puc{0}
{

}

template<typename T> shared_ptr<T>::~shared_ptr()
{
    if (--(*puc))
        delete p;
}
}
