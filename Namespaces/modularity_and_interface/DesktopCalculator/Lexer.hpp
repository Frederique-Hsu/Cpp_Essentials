/*!
 *  \file       Lexer.hpp
 *  \brief
 *
 */


#pragma once

namespace Lexer
{
enum class Kind : char
{
    number,
    name,
    minus,
    lp,
    rp,
    assign
};

class Token
{
public:
};

class TokenStream
{
public:
};

TokenStream ts;
}
