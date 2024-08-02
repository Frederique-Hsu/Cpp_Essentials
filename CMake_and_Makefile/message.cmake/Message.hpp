/*!
 *  \file       Message.hpp
 *  \brief
 *
 */


#pragma once


#include <string>

class Message
{
    friend std::ostream& operator<<(std::ostream& os, const Message& obj);
public:
    Message(const std::string& msg);

private:
    std::string m_message;

    std::ostream& printObject(std::ostream& os) const;
};
