/*!
 *  \file       Lexer.cpp
 *  \brief
 *
 */


#include "Lexer.hpp"


Lexer::TokenStream::TokenStream(std::istream& s) : ip{&s}, owns{false}, ct{Kind::end}
{
}

Lexer::TokenStream::TokenStream(std::istream* p) : ip{p}, owns{true}, ct{Kind::end}
{
}

Lexer::TokenStream::~TokenStream()
{
    close();
}

void Lexer::TokenStream::set_input(std::istream& s)
{
    close();
    ip = &s;
    owns = false;
}

void Lexer::TokenStream::set_input(std::istream* p)
{
    close();
    ip = p;
    owns = true;
}

void Lexer::TokenStream::close()
{
    if (owns)
    {
        delete ip;
    }
}

Lexer::Token Lexer::TokenStream::get()
{
    return ct;
}

Lexer::Token& Lexer::TokenStream::current()
{
    return ct;
}

// Lexer::TokenStream ts(std::cin);
