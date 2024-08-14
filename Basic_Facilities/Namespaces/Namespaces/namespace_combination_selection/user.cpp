/*!
 *  \file       user.cpp
 *  \brief
 *
 */

#include "user.h"

#include "A.h"
#include "B.h"


void fn()
{
    using namespace A;
    using namespace B;

    function('a');
    function(10);
}
