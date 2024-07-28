/*!
 *  \file       operator_new_delete.hpp
 *  \brief      
 *  
 */


#pragma once

#define __CPP_ALIGNED_NEW   1

extern "C++"
{
    typedef unsigned long   size_t;

    #if __CPP_ALIGNED_NEW
        enum class align_val_t : size_t
        {
        };
    #endif

    struct nothrow_t
    {
        #if __cplusplus >= 201103L
            explicit nothrow_t() = default;
        #endif
    };

    extern const nothrow_t nothrow;

    class exception
    {
    public:
        exception() noexcept {}
        virtual ~exception() noexcept {}
    #if __cplusplus >= 201103L
        exception(const exception&) = default;
        exception& operator=(const exception&) = default;
        exception(exception&&) = default;
        exception& operator=(exception&&) = default;
    #endif
    
    public:
        virtual const char* what() const noexcept;
    };

    class bad_alloc : public exception
    {
    public:
        bad_alloc() noexcept : exception() {}
        virtual ~bad_alloc() noexcept {}
    #if __cplusplus >= 201103L
        bad_alloc(const bad_alloc&) = default;
        bad_alloc& operator=(const bad_alloc&) = default;
    #endif

    public:
        virtual const char* what() const noexcept;
    };

    #if __cplusplus >= 201103L
        class bad_array_new_length : public bad_alloc
        {
        public:
            bad_array_new_length() noexcept : bad_alloc() {}
            virtual ~bad_array_new_length() noexcept {}

        public:
            virtual const char* what() const noexcept;
        };
    #endif

    void* operator new  (size_t);
    void* operator new[](size_t);
    
    void  operator delete  (void*) noexcept;
    void  operator delete[](void*) noexcept;

    void* operator new(size_t, void* placement_ptr) noexcept;
    void* operator new[](size_t, void* placement_ptr) noexcept;

    void  operator delete(void*, void*) noexcept;
    void  operator delete[](void*, void*) noexcept;

    void* operator new  (size_t, const nothrow_t&) noexcept;
    void* operator new[](size_t, const nothrow_t&) noexcept;

    void  operator delete  (void*, const nothrow_t&) noexcept;
    void  operator delete[](void*, const nothrow_t&) noexcept;

    #if __CPP_SIZED_DEALLOCATION
        void operator delete  (void*, size_t) noexcept;
        void operator delete[](void*, size_t) noexcept;
    #endif

    #if __CPP_ALIGNED_NEW
        void* operator new  (size_t, align_val_t);
        void* operator new[](size_t, align_val_t);
        void* operator new  (size_t, align_val_t, const nothrow_t&) noexcept;
        void* operator new[](size_t, align_val_t, const nothrow_t&) noexcept;

        void  operator delete  (void*, align_val_t) noexcept;
        void  operator delete[](void*, align_val_t) noexcept;
        void  operator delete  (void*, align_val_t, const nothrow_t&) noexcept;
        void  operator delete[](void*, align_val_t, const nothrow_t&) noexcept;

        #if __CPP_SIZED_DEALLOCATION
            void  operator delete  (void*, size_t, align_val_t) noexcept;
            void  operator delete[](void*, size_t, align_val_t) noexcept;
        #endif  /* __CPP_SIZED_DEALLOCATION */

    #endif  /* __CPP_ALIGNED_NEW */
}