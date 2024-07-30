/*!
 *  \file       SmartPointers.hpp
 *  \brief      
 *  
 */


#pragma once

#include <string>

template<typename T> class DiskPtr final
{
private:
    std::string identifier;
    T* in_core_address;

public:
    DiskPtr(const std::string& str);
    ~DiskPtr();

public:
    T* operator->();
    T& operator*();

private:
    void write_to_disk(T* disk_address, const std::string& disk_id);
    T* read_from_disk(const std::string& disk_id);
};

/*================================================================================================*/

template<typename T>
class Ptr
{
    T* pointer;
    T* array;
    int array_length;
public:
    template<int N> Ptr(T* p, T (&arr)[N]);
    Ptr(T* p, T* arr, int length);
    Ptr(T* p);
    ~Ptr();

public:
    Ptr& operator++();      // prefix:  ++ptr
    Ptr operator++(int);    // postfix: ptr++

    Ptr& operator--();      // prefix:  --ptr
    Ptr operator--(int);    // postfix: ptr--

    T& operator*();
    T* operator->();
    T* get() const;
};



#include "SmartPointers_Impl.hpp"