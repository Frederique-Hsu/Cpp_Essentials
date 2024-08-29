/*!
 *  \file       visitor.hpp
 *  \brief      
 *  
 */


#pragma once

class Visitor;

class Node
{
public:
    virtual ~Node() = default;
public:
    virtual void accept(Visitor&) = 0;
};

class Expr : public Node
{
public:
    void accept(Visitor&) override;
};

class Stmt : public Node
{
public:
    void accept(Visitor&) override;
};

class Visitor
{
public:
    virtual ~Visitor() = default;
public:
    virtual void accept(Expr&) = 0;
    virtual void accept(Stmt&) = 0;
};

class Do1_visitor : public Visitor
{
public:
    void accept(Expr&) override;
    void accept(Stmt&) override;
};

class Do2_visitor : public Visitor
{
public:
    void accept(Expr&) override;
    void accept(Stmt&) override;
};