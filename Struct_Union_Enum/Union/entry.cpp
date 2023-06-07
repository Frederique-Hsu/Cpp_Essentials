/*!
 *  \file       entry.cpp
 *  \brief
 *
 */


#include "entry.hpp"


namespace my
{
Entry::Entry(int number)
{
    using namespace std;

    type = Tag::number;
    i = number;
    // s.~string();
}

Entry::Entry(const std::string& text)
{
    using namespace std;

    type = Tag::text;
    new(&s) string(text);
}

/*!
 *  \remark     因为匿名union对象存在string成员，string具有用户定义的赋值运算符，所以Entry的赋值运算符被编译器delete掉了。
 *              故需要为Entry人为补充上。
 */
Entry& Entry::operator=(const Entry& entry)
{
    using namespace std;

    if (type == Tag::text && entry.type == Tag::text)
    {
        s = entry.s;
        return *this;
    }
    else if ((type == Tag::text) && (entry.type == Tag::number))
    {
        s.~string();

        i = entry.i;
        type = Tag::number;
        return *this;
    }
    else if ((type == Tag::number) && (entry.type == Tag::text))
    {
        new(&s) string(entry.s);
        type = Tag::text;
        return *this;
    }
    else if ((type == Tag::number) && (entry.type == Tag::number))
    {
        i = entry.i;
        return *this;
    }
}

Entry::~Entry()
{
    using namespace std;

    if (type == Tag::text)
        s.~string();
}

Entry::Entry(const Entry& entry)
{
    if (entry.type == Tag::number)
    {
        i = entry.i;
        type = Tag::number;
    }
    else if (entry.type == Tag::text)
    {
        new(&s) std::string(entry.s);
        type = Tag::text;
    }
}


/*!
 *  \remark     number()和text()两个访问函数首先检查type标签，如果是我们想要执行的访问，则放回对应值的引用；否则抛出异常。
 *              这样的union称为标签联合(tagged union)或者可判别联合(discriminated union)
 *
 */
int Entry::number() const
{
    if (type != Tag::number)
        throw Bad_entry{};
    return i;
}

std::string Entry::text() const
{
    if (type != Tag::text)
        throw Bad_entry{};
    return s;
}

void Entry::set_text(const std::string& str)
{
    if (type == Tag::text)
    {
        s = str;
    }
    else
    {
        new(&s) std::string(str);   // new的作用是显式地构造string
        type = Tag::text;
    }
}

void Entry::set_number(int n)
{
    using namespace std;

    if (type == Tag::text)
    {
        s.~string();    // 显式地销毁string
        type = Tag::number;
    }
    i = n;
}
}
