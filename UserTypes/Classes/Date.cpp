/*!
 *  \file       Date.cpp
 *  \brief
 *
 */


#include "Date.hpp"

#include <iostream>
#include <ctime>

Chrono::Date::Date(int day, Month month, int year)
    : m_day{day}, m_month{static_cast<int>(month)}, m_year(year)    // 成员初始化器
{
    if (m_year == 0)
    {
        m_year = default_date().year();
    }
    if (m_month == Month{})
    {
        m_month = default_date().month();
    }
    if (m_day == 0)
    {
        m_day = default_date().day();
    }
    if (!is_valid())
    {
        throw BadDate();
    }
}

bool Chrono::Date::is_valid()
{
    return Chrono::is_date(m_day, static_cast<Month>(m_month), m_year);
}

inline int Chrono::Date::day() const
{
    return m_day;
}

inline Chrono::Month Chrono::Date::month() const
{
    return m_month;
}

inline int Chrono::Date::year() const
{
    return m_year;
}

Chrono::Date& Chrono::Date::add_year(int n)
{
    if ((m_day == 29) && (m_month == Month::Feb) && !is_leap_year(m_year+n))
    {
        m_day = 1;
        m_month = Month::Mar;
    }
    m_year += n;
    return *this;
}

Chrono::Date& Chrono::Date::add_day(int n)
{
    int ndays = m_day + n;
    if (n > 0)
    {
        if (ndays <= 28)
        {
            m_day += n;
        }
        else if ( (28 < ndays) && (ndays <= 29) &&
                  (m_month == Month::Feb) && is_leap_year(m_year))
        {
            m_day += n;
        }
        else if ((29 < ndays) && (ndays <= 30))
        {
            switch (m_month)
            {
            case Chrono::Month::Feb:
                if (is_leap_year(m_year))
                {
                    m_day = 1;
                    m_month = Month::Mar;
                }
                else
                {
                    m_day = 2;
                    m_month = Month::Mar;
                }
                break;
            default:
                m_day += n;
            }
        }
        else if ((30 < ndays) && (ndays <= 31))
        {
            switch (m_month)
            {
            case Chrono::Month::Feb:
                if (is_leap_year(m_year))
                {
                    m_day = 2;
                }
                else
                {
                    m_day = 3;
                }
                m_month = Month::Mar;
                break;
            case Chrono::Month::Apr:
            case Chrono::Month::Jun:
            case Chrono::Month::Sep:
            case Chrono::Month::Nov:
                m_day = 1;
                m_month = static_cast<Month>(static_cast<int>(m_month) + 1);
                break;
            default:
                m_day += n;
                break;
            }
        }
        return *this;
    }
    if (n < 0)
    {
        // handling with the negative days
        return *this;
    }
    return *this;
}

Chrono::Date& Chrono::Date::add_month(int n)
{
    if (n == 0)
        return *this;

    if (n > 0)
    {
        int delta_year = n / 12;
        int remainder_month = static_cast<int>(m_month) + (n % 12);
        if (12 < remainder_month)
        {
            ++delta_year;
            remainder_month -= 12;
        }

        m_year += delta_year;
        m_month = static_cast<Month>(remainder_month);
        return *this;
    }
    if (n < 0)
    {
        // handle with the negative month
        return *this;
    }

    return *this;
}

bool Chrono::is_date(int day, Month month, int year)
{
    int ndays;
    switch (month)
    {
    case Chrono::Month::Feb:
        ndays = 28 + is_leap_year(year);
        break;
    case Chrono::Month::Apr:
    case Chrono::Month::Jun:
    case Chrono::Month::Sep:
    case Chrono::Month::Nov:
        ndays = 30;
        break;
    case Chrono::Month::Jan:
    case Chrono::Month::Mar:
    case Chrono::Month::May:
    case Chrono::Month::Jul:
    case Chrono::Month::Aug:
    case Chrono::Month::Oct:
    case Chrono::Month::Dec:
        ndays = 31;
        break;
    default:
        return false;
    }

    return (1 <= day) && (day <= ndays);
}

bool Chrono::is_leap_year(int year)
{
    return (year % 4 == 0);
}

const Chrono::Date& Chrono::default_date()
{
    std::time_t current_timestamp = std::time(NULL);
    struct tm* today_localtime = std::localtime(&current_timestamp);

    int year = today_localtime->tm_year + 1900;
    int month = today_localtime->tm_mon + 1;
    int day = today_localtime->tm_mday;

    static Date today{day, static_cast<Month>(month), year};
    return today;
}

bool Chrono::operator==(const Date& a, const Date& b)
{
    return a.day() == b.day() and
           a.month() == b.month() and
           a.year() == b.year();
}

bool Chrono::operator!=(const Date& a, const Date& b)
{
    return !(a == b);
}

Chrono::Date& Chrono::operator++(Date& date)
{
    return date.add_day(1);
}

Chrono::Date& Chrono::operator--(Date& date)
{
    return date.add_day(-1);
}

Chrono::Date& Chrono::operator+=(Date& date, unsigned int n)
{
    return date.add_day(n);
}

Chrono::Date& Chrono::operator-=(Date& date, unsigned int n)
{
    return date.add_day(-n);
}

Chrono::Date Chrono::operator+(Date date, unsigned int n)
{
    return date += n;
}

Chrono::Date Chrono::operator-(Date date, unsigned int n)
{
    return date -= n;
}

std::ostream& Chrono::operator<<(std::ostream& os, const Date& date)
{
    os << "Year: " << date.year()
       << ", Month: " << static_cast<int>(date.month())
       << ", Day: " << date.day()
       << std::endl;
    return os;
}

std::istream& Chrono::operator>>(std::istream& is, Date& date)
{
    std::cout << "Please enter the date.\nYear: ";
    int year, month, day;

    is >> year;
    std::cout << "Month: ";
    is >> month;
    std::cout << "Day: ";
    is >> day;
    date = Date(day, static_cast<Month>(month), year);

    return is;
}
