/*!
 * \file        calculator.hpp
 * \brief
 *
 */


#pragma once

#include <string>
#include <iostream>
#include <vector>

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
    Kind        kind;
    std::string string_value;
    double      number_value;
};

class TokenStream
{
public:
    TokenStream(std::istream& s);
    TokenStream(std::istream* p);
    ~TokenStream();
public:
    Token get();
    const Token& current();

    void set_input(std::istream& s);
    void set_input(std::istream* p);
private:
    void close();

    std::istream* ip;   // 指向输入流的指针
    bool owns;          // TokenStream是否拥有流？
    Token ct;           // 当前单词
};

double expr(bool get);
double term(bool get);
double prim(bool get);
double error(const std::string& s);

void calculate();
int desktop_calculator_main(int argc, char* argv[]);
std::vector<std::string> arguments(int argc, char* argv[]);
