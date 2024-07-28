/*!
 *  \file       operator_new_delete.cpp
 *  \brief      
 *  
 */


#include "operator_new_delete.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern "C++"
{
    const char* exception::what() const noexcept
    {
        return "exception";
    }

    const char* bad_alloc::what() const noexcept
    {
        return "bad_alloc";
    }
    
    #if __cplusplus >= 201103L
        const char* bad_array_new_length::what() const noexcept
        {
            return "bad_array_new_length";
        }
    #endif

    void* operator new(size_t size)
    {
        printf("void* operator new(size_t size), size = %ld bytes\n", size);

        void* ptr = malloc(size);
        if (ptr == nullptr)
        {
            throw bad_alloc();
        }
        return ptr;
    }

    void* operator new[](size_t size)
    {
        printf("void* operator new[](size_t size), size = %ld bytes\n", size);

        void* ptr = malloc(size);
        if (ptr == nullptr)
        {
            throw bad_array_new_length();
        }
        return ptr;
    }

    void  operator delete(void* ptr) noexcept
    {
        printf("void operator delete(void* ptr), ptr = %p\n", ptr);

        free(ptr);
    }

    void  operator delete[](void* ptr) noexcept
    {
        printf("void operator delete[](void* ptr), ptr = %p\n", ptr);

        free(ptr);
    }

    void* operator new(size_t, void* placement_ptr) noexcept
    {
        printf("void* operator new(size_t, void* placement_ptr), placement_ptr = %p\n", placement_ptr);

        return placement_ptr;
    }

    void* operator new[](size_t, void* placement_ptr) noexcept
    {
        printf("void* operator new[](size_t, void* placement_ptr), placement_ptr = %p\n", placement_ptr);

        return placement_ptr;
    }

    void  operator delete(void* ptr, void* placement_ptr) noexcept
    {
        printf("void  operator delete(void* ptr, void* placement_ptr), ptr = %p, placement_ptr = %p\n", 
               ptr, placement_ptr);
    }

    void  operator delete[](void* ptr, void* placement_ptr) noexcept
    {
        printf("void  operator delete[](void* ptr, void* placement_ptr), ptr = %p, placement_ptr = %p\n",
               ptr, placement_ptr);
    }

    void* operator new(size_t size, const nothrow_t& /* tag */) noexcept
    {
        printf("void* operator new(size_t size, const nothrow_t& tag), size = %ld bytes\n", size);

        void* ptr = malloc(size);
        if (ptr == nullptr)
        {
            printf("Failed to allocate memory for your object pointer.\n");
            return nullptr;
        }
        return ptr;
    }

    void* operator new[](size_t size, const nothrow_t& /* tag */) noexcept
    {
        printf("void* operator new[](size_t size, const nothrow_t& tag), size = %ld bytes\n", size);

        void* ptr = malloc(size);
        if (ptr == nullptr)
        {
            printf("Failed to allocate memory for your object pointers array.\n");
            return nullptr;
        }
        return ptr;
    }

    void  operator delete(void* ptr, const nothrow_t& /* tag */) noexcept
    {
        printf("void operator delete(void* ptr, const nothrow_t& tag), ptr = %p\n", ptr);

        free(ptr);
    };

    void  operator delete[](void* ptr, const nothrow_t& /* tag */) noexcept
    {
        printf("void operator delete[](void* ptr, const nothrow_t& tag), ptr = %p\n", ptr);

        free(ptr);
    }

    #if __CPP_SIZED_DEALLOCATION
        void operator delete(void* ptr, size_t size) noexcept
        {
            printf("void operator delete(void* ptr, size_t size), ptr = %p, size = %ld bytes\n", ptr, size);

            free(ptr);
        }

        void operator delete[](void* ptr, size_t size) noexcept
        {
            printf("void operator delete[](void* ptr, size_t size), ptr = %p, size = %ld bytes\n", ptr, size);

            free(ptr);
        }
    #endif  /* __CPP_SIZED_DEALLOCATION */

    #if __CPP_ALIGNED_NEW
        void* operator new(size_t size, align_val_t alignment)
        {
            printf("void* operator new(size_t size, align_val_t alignment), size = %ld bytes, alignment = %zu\n", 
                   size, 
                   static_cast<size_t>(alignment));

            void* ptr = aligned_alloc(static_cast<size_t>(alignment), size);
            if (ptr == nullptr)
            {
                printf("Failed to allocate the memory, because of %s\n", strerror(errno));
                throw bad_alloc();
            }
            return ptr;
        }

        void  operator delete(void* ptr, align_val_t alignment) noexcept
        {
            printf("void operator delete(void* ptr, align_val_t alignment), ptr = %p, alignment = %zu\n", 
                   ptr, 
                   static_cast<size_t>(alignment));

            free(ptr);
        }

        void* operator new[](size_t size, align_val_t alignment)
        {
            printf("void* operator new[](size_t size, align_val_t alignment), size = %ld bytes, alignment = %zu\n",
                   size,
                   static_cast<size_t>(alignment));

            void* ptr = aligned_alloc(static_cast<size_t>(alignment), size);
            if (ptr == nullptr)
            {
                printf("Failed to allocate the memory, because of %s\n", strerror(errno));
                throw bad_array_new_length();
            }
            return ptr;
        }

        void  operator delete[](void* ptr, align_val_t alignment) noexcept
        {
            printf("void operator delete[](void* ptr, align_val_t alignment), ptr = %p, alignment = %zu\n", 
                   ptr, 
                   static_cast<size_t>(alignment));
            
            free(ptr);
        }

        void* operator new(size_t size, align_val_t alignment, const nothrow_t& tag) noexcept
        {
            printf("void* operator new(size_t size, align_val_t alignment, const nothrow_t& tag), size = %ld bytes, alignment = %zu\n",
                   size, static_cast<size_t>(alignment));
            
            void* ptr = aligned_alloc(static_cast<size_t>(alignment), size);
            if (ptr == nullptr)
            {
                printf("Failed to allocate the memory, because %s\n", strerror(errno));
                return nullptr;
            }
            return ptr;
        }

        void  operator delete(void* ptr, align_val_t alignment, const nothrow_t& tag) noexcept
        {
            printf("void operator delete(void* ptr, align_val_t alignment, const nothrow_t& tag), ptr = %p, alignment = %zu\n", 
                   ptr, static_cast<size_t>(alignment));
            
            free(ptr);
        }

        void* operator new[](size_t size, align_val_t alignment, const nothrow_t& tag) noexcept
        {
            printf("void* operator new[](size_t size, align_val_t alignment, const nothrow_t& tag), size = %ld bytes, alignment = %zu\n",
                   size, static_cast<size_t>(alignment));
            
            void* ptr = aligned_alloc(static_cast<size_t>(alignment), size);
            if (ptr == nullptr)
            {
                printf("Failed to allocate the memory, because %s\n", strerror(errno));
                return nullptr;
            }
            return ptr;
        }

        void  operator delete[](void* ptr, align_val_t alignment, const nothrow_t& tag) noexcept
        {
            printf("void operator delete[](void* ptr, align_val_t alignment, const nothrow_t& tag), ptr = %p, alignment = %zu\n",
                   ptr, static_cast<size_t>(alignment));
            
            free(ptr);
        }

        #if __CPP_SIZED_DEALLOCATION
            void  operator delete(void* ptr, size_t size, align_val_t alignment) noexcept
            {
                printf("void operator delete(void* ptr, size_t size, align_val_t alignment), ptr = %p, size = %ld bytes, alignment = %zu\n",
                       ptr, size, static_cast<size_t>(alignment));
                
                free(ptr);
            }

            void  operator delete[](void* ptr, size_t size, align_val_t alignment) noexcept
            {
                printf("void operator delete[](void* ptr, size_t size, align_val_t alignment), ptr = %p, size = %ld bytes, alignment = %zu\n",
                       ptr, size, static_cast<size_t>(alignment));
                
                free(ptr);
            }
        #endif  /* __CPP_SIZED_DEALLOCATION */

    #endif  /* __CPP_ALIGNED_NEW */
}