/*!
 *  \file       Employee.hpp
 *  \brief
 *
 */


#pragma once

#include <string>
#include <list>

enum class Month : unsigned char
{
    Jan = 1,    Feb,    Mar,    Apr,    May,    Jun,
    Jul,        Aug,    Sep,    Oct,    Nov,    Dec
};

struct Date
{
    int year;
    Month month;
    int day;
};

class Employee
{
public:
    Employee(const char* firstname, const char middlename, const char* surname);
    virtual ~Employee() = default;
private:
    std::string first_name;
    std::string family_name;
    char middle_initial;
    Date hiring_date;
    short department;
public:
    virtual void print() const;
    std::string full_name() const;
};

class Manager : public Employee
{
public:
    Manager(const char* firstname, const char middlename, const char* surname, short mgmlevel);
private:
    std::list<Employee*> group;
    short level;
public:
    void print() const override;
};

void print_list(const std::list<Employee*>& employees);

class Director : public Manager
{
};

class Temporary
{
};

class Assistant : public Employee
{
};

class Temp : public Temporary, public Assistant
{
};

class Consultant : public Temporary, public Manager
{
};