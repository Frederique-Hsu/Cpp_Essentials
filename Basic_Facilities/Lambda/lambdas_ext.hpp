/*!
 *  \file       lambdas_ext.hpp
 *  \brief      Study the advanced topics of lambda expressions.
 *
 */


#pragma once

#include <string>
#include <functional>
#include <map>

/*!
 *  \section    lambda与this
 *
 *  \details    当lambda被用在成员函数中时，我们该如何访问类对象的成员呢？
 *
 *              我们的做法是把this添加到捕获列表中，这样类的成员就位于可被捕获的名字集合中了。
 */

namespace my
{
    using namespace std;

    class Request
    {
        function<map<string, string>(const map<string, string>)> oper;
    public:
        Request(const string& s);

        void execute();
    private:
        map<string, string> values;
        map<string, string> results;
    };
}
