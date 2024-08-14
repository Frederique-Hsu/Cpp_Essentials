/*!
 *  \file       calculator.cpp
 *  \brief
 *
 */


#include "calculator.hpp"

#include <map>
#include <cmath>
#include <sstream>

TokenStream::TokenStream(std::istream& s) : ip(&s), owns(false), ct{Kind::end}
/*!
 *  \warning    此处初始化ct不能使用ct(Kind::end)，而只能采用ct{Kind::end}, 为什么？
 *              因为Token是一个由非平凡的成员组成的结构体，结构体的初始化须用{}来进行。若ct的内部成员
 *              只初始化了kind成员，则其他2个成员则由编译器分别使用它们的默认值来初始化，
 *              即ct{Kind::end, std::string(), 0.0}
 */
{
}

TokenStream::TokenStream(std::istream* p) : ip(p), owns(true), ct{Kind::end}
{
}

TokenStream::~TokenStream()
{
    close();
}

void TokenStream::close()
{
    if (owns)
    {
        delete ip;
    }
}

void TokenStream::set_input(std::istream& s)
{
    close();
    ip = &s;
    owns = false;
}

void TokenStream::set_input(std::istream* p)
{
    close();
    ip = p;
    owns = true;
}

#if 0
Token TokenStream::get()
{
    char ch = 0;
    *ip >> ch;

    switch (ch)
    {
    case 0:
        return ct = {Kind::end};    // 赋值并返回
    case ';':
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
        return ct = {static_cast<Kind>(ch)};
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
        ip->putback(ch);
        *ip >> ct.number_value;
        ct.kind = Kind::number;
        return ct;
    default:
        if (std::isalpha(ch))
        {
            ip->putback(ch);
            *ip >> ct.string_value;
            ct.kind = Kind::name;
            return ct;
        }
        error("bad token");;
        return ct = {Kind::print};
    }
}
#else
Token TokenStream::get()
{
    char ch;
    do
    {
        if (!ip->get(ch))       // 跳过除'\n'之外的其他空白符
        {
            return ct = {Kind::end};
        }
    }
    while (ch != '\n' && std::isspace(ch));

    switch (ch)
    {
    case ';':
    case '\n':
        return ct = {Kind::print};
    default:
        if (std::isalpha(ch))
        {
            ct.string_value = ch;
            while (ip->get(ch) && std::isalnum(ch))
            {
                ct.string_value += ch;
            }
            ip->putback(ch);
            return ct = {Kind::name};
        }
    }
}
#endif

const Token& TokenStream::current()
{
}

/*================================================================================================*/

TokenStream ts{std::cin};

double expr(bool get)
{
    double left = term(get);

    while (true)
    {
        switch (ts.current().kind)
        {
        case Kind::plus:
            left += term(true);
            break;
        case Kind::minus:
            left -= term(true);
            break;
        default:
            return left;
        }
    }
}

double term(bool get)
{
    double left = prim(get);

    for (;;)
    {
        switch (ts.current().kind)
        {
        case Kind::mul:
            left *= prim(true);
            break;
        case Kind::div:
            if (auto d = prim(true))
            {
                left /= d;
                break;
            }
            return error("divide by 0");
        default:
            return left;
        }
    }
}

std::map<std::string, double> table;

double prim(bool get)
{
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
        double& v = table[ts.current().string_value];
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
        auto e = expr(true);
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

static int no_of_errors;

double error(const std::string& s)
{
    no_of_errors++;
    std::cerr << "error: " << s << std::endl;
    return 1;
}

void calculate()
{
    for (;;)
    {
        ts.get();
        if (ts.current().kind == Kind::end)
            break;
        if (ts.current().kind == Kind::print)
            continue;
        std::cout << expr(false) << std::endl;
    }
}

int desktop_calculator_main(int argc, char* argv[])
{
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    switch (argc)
    {
    case 1:
        break;
    case 2:
        ts.set_input(new std::istringstream(argv[1]));
        break;
    default:
        error("too many arguments");
        return 1;
    }

    calculate();
    return no_of_errors;
}

std::vector<std::string> arguments(int argc, char* argv[])
{
    std::vector<std::string> res;
    for (int i = 1; i != argc; ++i)
    {
        res.push_back(argv[i]);
    }
    return res;
}
