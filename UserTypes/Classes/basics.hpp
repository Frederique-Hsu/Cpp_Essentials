/*!
 *  \file       basics.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

// #define INDIRECT_ACCESS_TO_ACHIEVE_MUTABILITY

struct cache
{
    bool valid;
    std::string rep;
};

class Date
{
public:
    Date(int d, int m, int y);
    Date(int d, int m);     // current year
    /*!
     *  \attention  默认情况下，应该将单参数的构造函数声明为explicit
     *              如果确实想定义隐式构造函数，最好写下原因。否则代码的维护者可能怀疑你疏忽了。或者不懂这一原则。
     */
    explicit Date(int d);   // current month and current year
    Date();                 // default constructor, today as the date
    Date(const char* date);

private:
    int day;
    int month;
    int year;

    static Date default_date;

public:
    void add_year(int n);
    void add_month(int n)
    {
        month += n;
    }
    void add_day(int n);

    Date& increase_year(int n);
    Date& increase_month(int n);
    Date& increase_day(int n);

    int get_year() const;
    int get_month() const;
    int get_day() const;

    std::string string_rep() const;

    static void set_default(int d, int m, int y);

private:
#if defined(INDIRECT_ACCESS_TO_ACHIEVE_MUTABILITY)
    cache* c;
#else
    /*!
     *  \attention  将类的成员变量用mutable修饰，表示即使是const函数或const对象，
     *              也可以修改此成员。
     */
    mutable bool cache_valid;
    mutable std::string cache;
#endif

    void compute_cache_value() const;
    bool is_leap_year(int y);
};


struct Link
{
    int data;
    Link* predecessor;
    Link* successor;

    Link* insert(int x);
    void remove();
};
