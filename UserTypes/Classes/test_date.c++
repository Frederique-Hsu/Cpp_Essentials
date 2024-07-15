/*!
 *  \file       test_date.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include "test_date.h++"

void fill(std::vector<Chrono::Date>& dates)
{
    while (std::cin)
    {
        Chrono::Date date;
        try
        {
            std::cin >> date;
        }
        catch (Chrono::Date::BadDate& exception)
        {
            std::cout << "Throw out the exception from Date." << std::endl;
            continue;
        }
        dates.push_back(date);
    }
}

TEST(UTest4Date, CheckConstructionForDateObject)
{
    auto fn = [](Chrono::Date& date) {
        Chrono::Date lvb_day{16, Chrono::Month::Dec, date.year()};

        if ((date.day() == 29) && (date.month() == Chrono::Month::Feb))
        {
            /*! \todo   do something */
        }
    };
}
