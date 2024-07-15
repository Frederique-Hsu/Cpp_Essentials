/*!
 *  \file       Date.hpp
 *  \brief
 *
 */


#ifndef DATE_HPP
#define DATE_HPP

    #include <string>

    namespace Chrono
    {
        enum class Month
        {
            Jan = 1,    Feb,    Mar,    Apr,    May,    Jun,
            Jul,        Aug,    Sep,    Oct,    Nov,    Dec,
        };

        class Date
        {
        public:
            explicit Date(int day = {}, Month month = {}, int year = {});
            /*!
             *  \note   Date类不需要析构函数，因为Date不拥有资源，因此在离开
             *          作用域时不需要清理操作。
             */
            // ~Date();

            class BadDate   // For exception class
            {
            };

        private:
            int m_day;
            Month m_month;
            int m_year;

        public:
            int day() const;
            Month month() const;
            int year() const;

            std::string string_repr() const;
            void char_repr(char s[], int max) const;

            Date& add_year(int n);
            Date& add_month(int n);
            Date& add_day(int n);

        private:
            bool is_valid();
        };

        const Date& default_date();

        bool is_date(int day, Month month, int year);
        bool is_leap_year(int year);

        bool operator==(const Date& a, const Date& b);
        bool operator!=(const Date& a, const Date& b);
        Date& operator++(Date& date);
        Date& operator--(Date& date);
        Date& operator+=(Date& date, unsigned int n);
        Date& operator-=(Date& date, unsigned int n);
        Date operator+(Date date, unsigned int n);
        Date operator-(Date date, unsigned int n);

        std::ostream& operator<<(std::ostream& os, const Date& date);
        std::istream& operator>>(std::istream& is, Date& date);

        class Time
        {
        };

        class DateTime
        {
        private:
            Date m_date;
            Time m_time;
        public:
            DateTime(Date date, Time time);
            DateTime(int day, Month month, int year, Time time);
        };

    }   // namespace Chrono

#endif  /* DATE_HPP */
