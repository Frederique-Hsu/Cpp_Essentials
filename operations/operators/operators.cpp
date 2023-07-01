/*!
 *  \file       operators.cpp
 *  \brief
 *
 */



#include "operators.hpp"

#include <cstring>

#define STRING_COPY_TRADITIONAL_METHOD              1
#define STRING_COPY_ALTERNATIVE_METHOD              2
#define STRING_COPY_REMOVE_INDEX_METHOD             3
#define STRING_COPY_USE_POST_INCREMENT_METHOD       4
#define STRING_COPY_REMOVE_NULL_TERMINATOR_METHOD   5
#define STRING_COPY_METHOD                          STRING_COPY_REMOVE_NULL_TERMINATOR_METHOD

namespace my
{
void copy(char* dest, const char* src)
{
#if (STRING_COPY_METHOD == STRING_COPY_TRADITIONAL_METHOD)
    int length = std::strlen(src);
    for (int i = 0; i <= length; i++)
    {
        dest[i] = src[i];
    }
#elif (STRING_COPY_METHOD == STRING_COPY_ALTERNATIVE_METHOD)
    int i;
    for (i = 0; src[i] != 0; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = 0;
#elif (STRING_COPY_METHOD == STRING_COPY_REMOVE_INDEX_METHOD)
    while (*src != 0)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = 0;
#elif (STRING_COPY_METHOD == STRING_COPY_USE_POST_INCREMENT_METHOD)
    while (*src != 0)
    {
        *dest++ = *src++;       // 后置运算符允许我们先使用值再递增它
    }
    *dest = 0;
#elif (STRING_COPY_METHOD == STRING_COPY_REMOVE_NULL_TERMINATOR_METHOD)
    while ((*dest++ = *src++) != 0)     // (*dest++ = *src++) 的值是 *src
    {
    }
#else
    while (*dest++ = *src++);
#endif
}
}
