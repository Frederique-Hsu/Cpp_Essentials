/*!
 *  \file       utils.cpp
 *  \brief
 *
 */


#include "utils.hpp"

#include <sstream>

std::vector<std::string> split(const std::string& s)
{
#if true
    using std::string;
    using std::vector;
    // using std::istringstream;
#else
    using namespace std;
#endif

    vector<string> res;
    std::istringstream iss(s);
    for (string buf; iss >> buf; )
    {
        res.push_back(buf);
    }
    return res;
}

bool Chrono::operator==(const Date& date, const std::string& date_str)
{
    std::vector<std::string> fields = split(date_str);

    int year = std::atoi(fields[0].c_str());
    int month = std::atoi(fields[1].c_str());
    int day = std::atoi(fields[2].c_str());

    if ((year == date.year()) and (month == date.month()) and (day == date.day()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Chrono::format(const Date& date)
{
    char str[0xFF] = {0x00};
    std::sprintf(str, "%d %02d %02d", date.year(), date.month(), date.day());
    return std::string(str);
}

/*!
 *  \attention  参数依赖查找
 */
void frmt(Chrono::Date date, int i)
{
    std::string s = format(date);   // OK: called Chrono::format
    (void)i;
    // std::string t = format(i);      // Error: 作用域中没有找到format(int)的定义
}
