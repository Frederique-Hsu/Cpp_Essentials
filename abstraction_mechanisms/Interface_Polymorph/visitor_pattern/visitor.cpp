/*!
 *  \file       visitor.cpp
 *  \brief      
 *  
 */


#include "visitor.hpp"

#include <iostream>

void Expr::accept(Visitor& v)
{
    v.accept(*this);
}

void Stmt::accept(Visitor& v)
{
    v.accept(*this);
}

void Do1_visitor::accept(Expr&)
{
    std::cout << "Do1 to Expr node" << std::endl;
}

void Do1_visitor::accept(Stmt&)
{
    std::cout << "Do1 to Stmt node" << std::endl;
}

void Do2_visitor::accept(Expr&)
{
    std::cout << "Do2 to Expr node" << std::endl;
}

void Do2_visitor::accept(Stmt&)
{
    std::cout << "Do2 to Stmt node" << std::endl;
}