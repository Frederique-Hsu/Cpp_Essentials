/*!
 *  \file       test_return_type_relaxation.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "return_type_relaxation.hpp"
#include "../utils/finalize.hpp"
#include "../utils/finalize.cpp"

TEST(UTest4ReturnTypeRelaxation, CheckOverridedMethodCanReturnDerivedType)
{
    auto user = [](Expr* ptr)
    {
        Expr* expr_ptr = ptr->new_expr();

        auto deleter = finalize([&]() {
            delete expr_ptr;
        });
    };

    auto user2 = [](Cond* pc, Addition* pa)
    {
        Cond* p1 = pc->clone();
        Addition* p2 = pa->clone();

        auto deleter = finalize([&]() {
            delete p1;
            delete p2;
        });
    };

    auto user3 = [](Cond* pc, Expr* pe)
    {
        Cond* p1 = pc->clone();
        /*  error:  Expr::clone() just returns an Expr* object pointer, cannot be used to initialize the concrete 
         *          object of Cond*
         */
        // Cond* p2 = pe->clone();

        auto remover = finalize([&]() {
            delete p1;
            // delete p2;
        });
    };

    /*========================================================================*/

    Expr* cond_obj_ptr = new Cond;
    Expr* addition_obj_ptr = new Addition(15);
    auto deleter = finalize([&cond_obj_ptr, &addition_obj_ptr]() {
        delete addition_obj_ptr;
        delete cond_obj_ptr;
    });

    std::cout << "/*========================================================================*/\n" << std::endl;

    user(cond_obj_ptr);
    std::cout << "/*========================================================================*/\n" << std::endl;

    Cond cond_obj;
    Addition addition_obj(10);

    user2(&cond_obj, &addition_obj);
    std::cout << "/*========================================================================*/\n" << std::endl;
    
    user3(&cond_obj, cond_obj_ptr);
}