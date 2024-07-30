/*!
 *  \file       SmartPointers_Impl.hpp
 *  \brief      
 *  
 */


#include <stdexcept>

template<typename T>
DiskPtr<T>::DiskPtr(const std::string& str) : identifier{str}, in_core_address{nullptr}
{
}

template<typename T>
DiskPtr<T>::~DiskPtr()
{
    if (in_core_address != nullptr)
    {
        write_to_disk(in_core_address, identifier);
    }
}

template<typename T>
T* DiskPtr<T>::operator->()
{
    if (in_core_address == nullptr)
    {
        in_core_address = read_from_disk(identifier);
    }
    return in_core_address;
}

template<typename T>
void DiskPtr<T>::write_to_disk(T* disk_address, const std::string& disk_id)
{
    /*!
     *  \todo   To be implemented here in the future
     */
}

template<typename T>
T* DiskPtr<T>::read_from_disk(const std::string& disk_id)
{
    /*!
     *  \todo   To be implemented here in the future.
     */
    return in_core_address;
}

/*================================================================================================*/

template<typename T> template<int N>
Ptr<T>::Ptr(T* p, T (&arr)[N]) : pointer{p}, array{arr}, array_length{N}
{
}

template<typename T>
Ptr<T>::Ptr(T* p, T* arr, int length) : pointer{p}, array{arr}, array_length{length}
{
}

template<typename T>
Ptr<T>::Ptr(T* p) : pointer{p}, array{p}, array_length{0}
{
}

template<typename T>
Ptr<T>::~Ptr()
{
    /*!
     *  \todo   to be implemented here in the future.
     */
}

template<typename T>
Ptr<T>& Ptr<T>::operator++()
{
    if (pointer >= array + array_length - 1)
    {
        throw std::out_of_range("already exceeded the upper boundary of array");
    }
    ++pointer;
    return *this;
}

template<typename T>
Ptr<T> Ptr<T>::operator++(int)
{   
    if (pointer >= array + array_length - 1)
    {
        throw std::out_of_range("already exceeded the upper boundary of array");
    }
    Ptr<T> old(pointer, array, array_length);
    ++pointer;
    return old;
}

template<typename T>
Ptr<T>& Ptr<T>::operator--()
{
    if (pointer <= array)
    {
        throw std::out_of_range("already exceeded the lower boundary of array");
    }
    --pointer;
    return *this;
}

template<typename T>
Ptr<T> Ptr<T>::operator--(int)
{
    if (pointer <= array)
    {
        throw std::out_of_range("already exceeded the lower boundary of array");
    }
    Ptr<T> old(pointer, array, array_length);
    --pointer;
    return old;
}

template<typename T>
T& Ptr<T>::operator*()
{
    return *pointer;
}

template<typename T>
T* Ptr<T>::operator->()
{
    return pointer;
}

template<typename T>
T* Ptr<T>::get() const
{
    return pointer;
}