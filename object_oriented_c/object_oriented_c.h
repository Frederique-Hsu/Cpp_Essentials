/*!
 *  \file       object_oriented_c.h
 *  \brief      
 *  
 */


#pragma once


#include <memory.h>
#include <stdlib.h>


#define P(x, y)             P_PRIMITIVE(x, y)
#define P_PRIMITIVE(x, y)   x##y


/*!
 *  \typedef    type-definitions for various return types.
 */
typedef void            (*RVOID)();
typedef int             (*RINT)();
typedef short           (*RSHORT)();
typedef long            (*RLONG)();
typedef float           (*RFLOAT)();
typedef double          (*RDOUBLE)();
typedef long double     (*RLDOUBLE)();
typedef unsigned int    (*RUINT)();
typedef unsigned short  (*RUSHORT)();
typedef unsigned long   (*RULONG)();

/*!
 *  \class  Object
 */
typedef struct
{
    RVOID*  vtbl;
} Object;

void SetupObjectInheritance(RVOID* vtbl);
void Object_ctor(Object* this);
void Object_dtor(Object* this);

enum
{
    vstart_Object = -1,
    vi_Object_dtor,
    vend_Object
};


/*!
 *  \note   Set-up the Vtbls
 */
#define INITIALIZE_OOC                                  \
    do                                                  \
    {                                                   \
        RVOID* v = vtblList;                            \
        int i = sizeof vtblList / sizeof(*vtblList);    \
        while (i--)                                     \
        {                                               \
            ((void (*)())(*v++))();                     \
        }                                               \
    }                                                   \
    while (0)                                           

/*!
 *  \note   Macros for calling non-virtual (regular) methods
 */
#define CALL(class, method)     class##_##method
#define CALLME(method)          P(CLASS, P(_, method))

