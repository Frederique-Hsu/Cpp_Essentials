/*!
 *  \file       utils.hpp
 *  \brief
 *
 */


#pragma once


#include <vector>
#include <string>


std::vector<std::string> split(const std::string& s);


namespace Chrono
{
class Date
{
    int m_year;
    int m_month;
    int m_day;
public:
    Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day)
    {
    }
    int year() const
    {
        return m_year;
    }
    int month() const
    {
        return m_month;
    }
    int day() const
    {
        return m_day;
    }
};

bool operator==(const Date&, const std::string& date_str);

std::string format(const Date&);
}

void frmt(Chrono::Date date, int i);
