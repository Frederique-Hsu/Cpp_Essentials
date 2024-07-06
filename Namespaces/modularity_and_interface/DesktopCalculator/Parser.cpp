/*!
 *  \file       Parser.cpp
 *  \brief      Implement the module of Parser.
 *
 */


#include "Parser.hpp"
#include "Lexer.hpp"
#include "Table.hpp"
#include "Error.hpp"

double Parser::prim(bool get)
{
#if false
    using Lexer::ts;
    using Lexer::Kind;
    using Error::error;
    using Table::table;
#else
    using namespace Lexer;
    using namespace Error;
    using namespace Table;
#endif

    if (get)
    {
        ts.get();
    }

    switch (ts.current().kind)
    {
    case Kind::number:
    {
        double v = ts.current().number_value;
        ts.get();
        return v;
    }
    case Kind::name:
    {
        double& v = table[Lexer::ts.current().string_value];
        if (ts.get().kind == Kind::assign)
        {
            v = expr(true);
        }
        return v;
    }
    case Kind::minus:
        return -prim(true);
    case Kind::lp:
    {
        double e = expr(true);
        if (ts.current().kind != Kind::rp)
        {
            return error("')' expected");
        }
        ts.get();
        return e;
    }
    default:
        return error("primary expected");
    }
}

double Parser::term(bool get)
{
    (void)get;

    return double{};
}

double Parser::expr(bool get)
{
    (void)get;

    return double{};
}
