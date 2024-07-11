/*!
 *  \file       my_string.c
 *  \brief
 *
 */


#include "my_string.h"

char* strcpy(char* target, const char* source)
{
    char* dest = target;
    while ((*target++ = *source++) != '\0')
    {
    }
    return dest;
}

int strcmp(const char* a, const char* b)
{
    while (*a == *b)
    {
        if (*a == '\0')
        {
            return 0;
        }
        a++;
        b++;
    }
    return (*a - *b);
}

int strlen(const char* str)
{
    int len = 0;
    while (*str++ != '\0')
    {
        len++;
    }
    return len;
}
