/*!
 *  \file       test_static_polymorphism.cc
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "dynamic_polymorphism.hpp"
#include "static_polymorphism.hpp"

TEST(UTester4DynamicPolymorphism, Check_How_Dynamic_Polymorphism_Works)
{
    using namespace dynamic_polymorphism;

    base *objptr = new derived;
    objptr->doWork();
    delete objptr;
}

TEST(UTester4StaticPolymorphism,  Check_How_Static_Polymorphism_Works)
{
    using namespace static_polymorphism;
    /*!
     *  \note   we expressed our interface "worker" in the concept, 
     *          and on the concrete implementation, we remove the inheritance.
     *          with the final alias, we can then use the concrete type we want.
     */
    my_worker w;
    w.doWork();
}

TEST(UTester4CRTP, Check_How_CRTP_Works)
{
    using namespace static_polymorphism;

    derived dobj;
    dobj.doWork();
    dobj.doWorkImpl();

    base<derived> bobj;
    bobj.doWork();
}