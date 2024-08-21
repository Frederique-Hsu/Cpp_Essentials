/*
 *  \file       return_type_relaxation.hpp
 *  \brief      
 *  
 */


#pragma once


/*!
 *  \note   There is a relaxation of the rule that the type of an overriding function must be the same
 *          as the type of a virtual function it overrides.
 *          That is:  if the original return type was Base*, then the return type of overriding function 
 *          may be Derived*, provided Base is a public base of Derived.
 *          Similarly, a return type of Base& may be relaxed to Derived&.
 *          This is sometimes called the \a covariant return rule.
 * 
 *  \attention  This relaxation applies only to return type that are pointers or references,
 *              and not to "smart pointer" such as unique_ptr
 *              In particular, there is not a similar relaxation of the rules for argument types, because
 *              that would lead to type violations.
 */


class Expr
{
public:
    Expr();
    Expr(const Expr&);
    virtual ~Expr();

public:
    /*! \interface  */
    virtual Expr* new_expr() = 0;
    virtual Expr* clone() = 0;
};

class Cond : public Expr
{
public:
    Cond();
    Cond(const Cond&);
    ~Cond();

public:
    /*!
     *  \attention  A derived class can override \a new_expr() and \a clone()
     *              to return an object of its own type.
     */
    Cond* new_expr() override;
    Cond* clone() override;
};

class Addition : public Expr
{
public:
    Addition(int extra);
    Addition(const Addition& rhs);
    ~Addition();

private:
    int m_extra;

public:
    Addition* new_expr() override;
    Addition* clone() override;
};