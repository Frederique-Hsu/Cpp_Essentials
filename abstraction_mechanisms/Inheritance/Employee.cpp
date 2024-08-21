/*!
 *  \file       Employee.cpp
 *  \brief
 *
 */


#include "Employee.hpp"

#include <iostream>


Employee::Employee(const char* firstname, const char middlename, const char* surname)
    : first_name{firstname}, family_name{surname}, middle_initial{middlename}
{
    hiring_date = Date{2015, Month::May, 18};
    department = 12;
}

Manager::Manager(const char* firstname, const char middlename, const char* surname, short mgmlevel)
    : Employee(firstname, middlename, surname), level{mgmlevel}
{
}

std::string Employee::full_name() const
{
    if (middle_initial == ' ')
    {
        return first_name + " " + family_name;
    }
    else
    {
        return first_name + ' ' + middle_initial + ". " + family_name;
    }
}

void Employee::print() const
{
    std::cout << "Employee's name is " << full_name() << std::endl;
}

void Manager::print() const
{
    std::cout << "Manager's name is " << full_name() << std::endl;

    std::cout << "Level is " << level << std::endl;
}

void print_list(const std::list<Employee*>& employees)
{
    for (Employee* employee : employees)
    {
        employee->print();
    }
}