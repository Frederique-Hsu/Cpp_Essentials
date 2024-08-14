/*!
 *  \file       my.string.cpp
 *  \brief
 *
 */


#include "my.string.hpp"

#ifdef __cplusplus
namespace my
{
    extern "C"
    {
#endif

        char* istrcpy(char* target, const char* source)
        {
            char* dest = target;
            while ((*target++ = *source++) != '\0')
            {
            }
            return dest;
        }

        int istrcmp(const char* a, const char* b)
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

        int istrlen(const char* str)
        {
            int len = 0;
            while (*str++ != '\0')
            {
                len++;
            }
            return len;
        }

#ifdef __cplusplus
    }
}
#endif
