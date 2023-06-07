/*!
 *  \file       entry.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

namespace my
{
class Entry
{
private:
    enum class Tag
    {
        number,
        text
    };
    Tag type;

    /*!
     *  \note   匿名联合 anonymous union
     *          匿名联合是一个对象而非一种类型，无需对象名就能直接访问它的成员。
     *          因此，使用匿名联合的成员的方式与使用类成员的方式完全一样，只是需要谨记同一时刻只能使用union的一个成员就可以了。
     */
    union {
        int i;
        std::string s;      // string有默认构造函数、拷贝操作和析构函数
    };
public:
    struct Bad_entry    // 用于处理异常
    {
    };

    // std::string name;
public:
    explicit Entry(int number);
    explicit Entry(const std::string& text);
    ~Entry();
    Entry& operator=(const Entry&);
    Entry(const Entry&);
public:
    int number() const;
    std::string text() const;

    void set_number(int n);
    void set_text(const std::string& str);
};
}
