/*!
 *  \file       basics.cpp
 *  \brief
 *
 */


#include "basics.hpp"

#include <ctime>

static void get_current_date(int* year, int* month, int* day)
{
    std::time_t today = std::time(NULL);
    struct tm* current_timestamp = std::localtime(&today);

    *year = current_timestamp->tm_year + 1900;
    *month = current_timestamp->tm_mon + 1;
    *day = current_timestamp->tm_mday;
}

Date Date::default_date{1, 10, 1949};

Date::Date(int d, int m, int y)
{
    day = d ? d : default_date.day;
    month = m ? m : default_date.month;
    year = y ? y : default_date.year;
}

void Date::set_default(int d, int m, int y)
{
    default_date = {d, m, y};
}

Date::Date()
{
    get_current_date(&year, &month, &day);
}

/*!
 *  \warning    'explicit' can only be specified inside the class definition.
 */
/* explicit */ Date::Date(int d)
{
    get_current_date(&year, &month, &day);

    day = d;
}

Date::Date(int d, int m)
{
    get_current_date(&year, &month, &day);

    day = d;
    month = m;
}

void Date::add_day(int d)
{
    day += d;
}

/*!
 *  \attention  在类外部实现成员函数时，不要加上inline修饰。
 *              C++11已经不再支持这样的特性了。
 */
/* inline */ void Date::add_year(int n)
{
    year += n;
}

int Date::get_year() const
{
    /*!
     *  \note   常量成员函数参数列表后的const指出该函数不会修改Date的状态。
     *          若编程人员在实现该成员函数时，改变了Date的成员变量，编译器会捕获试图违反此承诺的代码。
     */
    return year;
}

int Date::get_month() const
{
    return month;
}

int Date::get_day() const
{
    return day;
}

std::string Date::string_rep() const
{
#if defined(INDIRECT_ACCESS_TO_ACHIEVE_MUTABILITY)
    if (!c->valid)
    {
        compute_cache_value();
        c->valid = true;
    }
    return c->rep;
#else
    if (!cache_valid)
    {
        compute_cache_value();
        cache_valid = true;
    }
    return cache;
#endif
}

void Date::compute_cache_value() const
{
}

Date& Date::increase_year(int n)
{
    if ((day == 29) and (month == 2) and (!is_leap_year(year + n)))
    {
        day = 1;
        month = 3;
    }
    year += n;
    return *this;
}

bool Date::is_leap_year(int y)
{
    if (y % 4 == 0)
        return true;
    else
        return false;
}

Date& Date::increase_month(int n)
{
    if (month + n >= 13)
    {
        month = (month + n - 12);
        year += 1;
    }
    else
    {
        month += n;
    }
    return *this;
}

Date& Date::increase_day(int n)
{
    day += n;
    return *this;
}


Link* Link::insert(int x)
{
    return predecessor = new Link{x, predecessor, this};
}

void Link::remove()
{
    if (predecessor)
    {
        predecessor->successor = successor;
    }
    if (successor)
    {
        successor->predecessor = predecessor;
    }
    delete this;
}
