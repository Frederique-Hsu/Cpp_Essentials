/*!
 *  \file       lambda.cpp
 *  \brief
 *
 */


#include "lambda.hpp"

#include <iostream>

void print_all(const std::map<std::string, int>& m, const std::string& label)
{
    using namespace std;

    cout << label << ":\n{\n";
    for_each(m.begin(),
             m.end(),
             [](const pair<string, int>& p)
             {
                 cout << p.first << ", " << p.second << "\n";
             });
    cout << "}" << endl;
}

void Request::execute()
{
    [this](){
        results = oper(values);
    };
}

void calculate_algo(vector<int>& vec)
{
    int count = vec.size();

    std::generate(vec.begin(),
                  vec.end(),
                  [count]() mutable
                  {
                      return --count;
                  });
    cout << "current count is " << count << endl;
}

void reverse_string(string& str1, string& str2)
{
    auto reverse = [&](char* begin, char* end){
        while (1 < end - begin)
        {
            swap(*begin++, *--end);
        }
    };

    reverse(&str1[0], &str1[0] + str1.size());
    reverse(&str2[0], &str2[0] + str2.size());
}
