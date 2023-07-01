/*!
 *  \file       calculator.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

enum class Kind : char
{
    name,
    number,
    end,
    plus    = '+',
    minus   = '-',
    mul     = '*',
    div     = '/',
    print   = ';',
    assign  = '=',
    lp      = '(',
    rp      = ')'
};

struct Token
{
    Kind            kind;
    std::string     string_value;
    double          number_value;
};

struct Enode
{
    Kind oper;
    Enode *left;
    Enode *right;
};

class TokenStream
{
public:
    TokenStream(std::istream& s);
    TokenStream(std::istream* p);
    ~TokenStream();
private:
    std::istream* ip;
    bool owns;
    Token ct;
public:
    Token get();
    const Token& current();

    void set_input(std::istream& s);
    void set_input(std::istream* p);
private:
    void close();
};

Enode* expr(bool get);
Enode* term(bool get);
