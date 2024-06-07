/*!
 *  \file   functions.cpp
 *  \brief  Implement the function definitions here
 *
 */


#include "functions.hpp"


void swap(int* p, int* q)
{
    int t = *p;
    *p = *q;
    *q = t;
}

#if defined(FUNCTION_REDEFINITION)
    void f(int x)   /*! \note   we can modify x here */
    {
        (void)x;
    }

    void f(const int x)     /*! \note   we cannot modify x here */
    {
        (void)x;
    }
#endif

/*!
 *  \note   Function argument names are not part of the function type,
 *          and need not be identical in different declarations.
 */
int& max(int& x1, int& x2, int& x3)
{
    return (x1 > x2) ? ( (x1 > x3) ? x1 : x3) : ((x2 > x3) ? x2 : x3);
}

/*================================================================================================*/

int fac2(int n)
{
    if ( n > 1)
    {
        return n * fac2(n-1);
    }
    return 1;
}

/*================================================================================================*/

int* fp()
{
    int local = 1;
    // ...

    /*!
     *  \warning    a pointer to a local non-static variable should never be returned.
     *              The contents of the location pointed to will change unpredictably.
     */
    return &local;
}

int& fr()
{
    int local = 1;
    // ...

    /*!
     *  \warning    An equivalent error can also occur when using reference for the local variable.
     */
    return local;
}

/*================================================================================================*/

