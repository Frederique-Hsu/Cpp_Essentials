/*!
 *  \file       users.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iostream>
#include <string>
#include <initializer_list>
#include <set>

class Person
{
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
    friend bool operator<(const Person a, const Person b);
public:
    enum class Gender
    {
        Male = 0,
        Female = 1
    };

    Person(const char* name, Gender gender, unsigned short age);
private:
    std::string m_name;
    Gender m_gender;
    unsigned short m_age;
};

class Users : public std::set<Person>
{
    friend std::ostream& operator<<(std::ostream& os, const Users& users);
public:
    Users(const Person& person);
    Users(const std::initializer_list<Person>& persons);
    
    std::size_t size() const;
};