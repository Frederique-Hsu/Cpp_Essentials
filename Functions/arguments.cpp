/*!
 *  \file       arguments.cpp
 *  \brief
 *
 */


#include "arguments.hpp"


/*!
 *  \section        Implementation
 */

int* find(int* first, int* last, int v)
{
    while ((first != last) && (*first != v))
    {
        ++first;
    }
    return first;
}
