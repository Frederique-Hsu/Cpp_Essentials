/*!
 *  \file       arch-dependent-x86_64.cpp
 *  \brief
 *
 */


#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
    #error cmake_arch   i386
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
    #define cmake_arch   x86_64
#endif