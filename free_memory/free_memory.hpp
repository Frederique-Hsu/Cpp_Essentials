/*!
 *  \file       free_memory.hpp
 *  \brief
 *
 */


#ifndef FREE_MEMORY_HPP
#define FREE_MEMORY_HPP

    #include <string>

    std::string reverse(const std::string& s);

    char* save_string(const char* p);


    void* operator new(size_t n);
    void operator delete(void* p);
    void* operator new[](size_t n);
    void operator delete[](void* p);

#endif  /* FREE_MEMORY_HPP */
