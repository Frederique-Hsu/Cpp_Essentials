/*!
 *  \file       my_string.hpp
 *  \brief
 *
 */


#pragma once

#ifdef __cplusplus
namespace my
{
    extern "C"
    {
#endif
        char* istrcpy(char* target, const char* source);
        int istrcmp(const char* a, const char* b);
        int istrlen(const char* str);
#ifdef __cplusplus
    }
}
#endif
