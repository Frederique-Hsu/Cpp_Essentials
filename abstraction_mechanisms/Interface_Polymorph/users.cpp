/*!
 *  \file       users.cpp
 *  \brief
 *
 */


#include "users.hpp"

Person::Person(const char* name, Gender gender, unsigned short age)
    : m_name{name}, m_gender{gender}, m_age{age}
{
}

Users::Users(const Person& person) : std::set<Person>()
{
    std::set<Person>::emplace(person);
}

Users::Users(const std::initializer_list<Person>& persons) : std::set<Person>(persons)
{
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os << "Name: " << person.m_name
       << ", Gender: " << (person.m_gender == Person::Gender::Male ? "Male" : "Female")
       << ", Age: " << person.m_age << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Users& users)
{
    for (const auto& user : users)
    {
        os << user << std::endl;
    }
    return os;
}

bool operator<(const Person a, const Person b)
{
    return a.m_age < b.m_age;
}

std::size_t Users::size() const
{
    return std::set<Person>::size();
}