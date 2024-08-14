/*!
 *  \file       lambda.hpp
 *  \brief
 *
 */


#pragma once

#include <iostream>
#include <map>
#include <functional>

using namespace std;

/* Prototype =====================================================================================*/
template<typename U, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<U, V>& p);

void print_all(const std::map<std::string, int>& m, const std::string& label);

class Request
{
public:
    Request(const string& s);
private:
    function<map<string, string>(const map<string, string>&)> oper;
    map<string, string> values;
    map<string, string> results;
public:
    void execute();
};

void calculate_algo(vector<int>& vec);

void reverse_string(string& str1, string& str2);


/* Implementation ================================================================================*/
template<typename U, typename V>
std::ostream& operator<<(std::ostream& os, std::pair<U, V>& p)
{
    return os << "{" << p.first << ", " << p.second << "}";
}


