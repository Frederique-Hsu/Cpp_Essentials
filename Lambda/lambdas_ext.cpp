/*!
 *  \file       lambdas_ext.cpp
 *  \brief
 *
 */


#include "lambdas_ext.hpp"

namespace my
{
    Request::Request(const string& s) : values{}, results{}
    {
        values.emplace(pair<string, string>{s, ""});
    }

    void Request::execute()
    {
        /*!
         *  \note   this指针作为捕获列表，意味着成员通过this访问，而非拷贝到lambda表达式中。
         *          所以，该处是引用的捕获方式.
         *          但注意，[this]与[=]互不兼容，稍有不慎就可能在多线程程序中产生竞争条件。
         */
        [this]() {
            results = oper(values);
        };
    }
}
