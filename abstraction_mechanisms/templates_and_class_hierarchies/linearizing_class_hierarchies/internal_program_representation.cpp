/*!
 *  \file       internal_program_representation.cpp
 *  \brief      
 *  
 */


#include "internal_program_representation.hpp"

namespace ipr
{
    Node::Node(CategoryCode c) : node_id{0}, category{c}
    {
    }

    Expr::Expr(CategoryCode c) : Node(c)
    {
    }

    Stmt::Stmt(CategoryCode c) : Expr(c)
    {
    }

    Decl::Decl(CategoryCode c) : Stmt(c)
    {
    }
}