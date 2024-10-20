/*!
 *  \file       test_name_binding.h++
 *  \brief      
 *  
 */


#pragma once


class Pool
{
public:
    template<typename T> T* get();
    template<typename T> void release(T*);
};

template<typename Allocator> void access(Allocator& allocator);

void user(Pool& pool);