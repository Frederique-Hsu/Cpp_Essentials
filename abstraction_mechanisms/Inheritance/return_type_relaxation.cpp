/*!
 *  \file       return_type_relaxation.cpp
 *  \brief      
 *  
 */


#include "return_type_relaxation.hpp"

#ifdef DEBUG_WITH_LOG
    #include <iostream>
#endif

Expr::Expr() 
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Expr::Expr() default constructor" << std::endl;
#endif
}

Expr::Expr(const Expr&) 
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Expr::Expr(const Expr&) copy constructor" << std::endl;
#endif
}

Expr::~Expr()
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Expr::~Expr() destructor" << std::endl;
#endif
}

Cond::Cond() : Expr() 
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Cond::Cond() default constructor" << std::endl;
#endif
}

Cond::Cond(const Cond& rhs) : Expr(rhs) 
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Cond::Cond(const Cond&) copy constructor" << std::endl;
#endif
}

Cond::~Cond()
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Cond::~Cond() destructor" << std::endl;
#endif
}

Cond* Cond::new_expr()
{
    return new Cond();
}

Cond* Cond::clone()
{
    return new Cond(*this);
}

Addition::Addition(int extra) : Expr(), m_extra{extra}
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Addition::Addition(int extra) constructor" << std::endl;
#endif
}

Addition::Addition(const Addition& rhs) : Expr(rhs), m_extra{rhs.m_extra}
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Addition::Addition(const Addition& rhs) copy constructor" << std::endl;
#endif
}

Addition::~Addition()
{
#ifdef DEBUG_WITH_LOG
    std::cout << "Called Addition::~Addition() destructor" << std::endl;
#endif
}

Addition* Addition::new_expr()
{
    return new Addition(int{});
}

Addition* Addition::clone()
{
    return new Addition(*this);
}