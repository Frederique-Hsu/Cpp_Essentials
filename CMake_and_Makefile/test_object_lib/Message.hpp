/*!
 *  \file       Message.hpp
 *  \brief      
 *  
 */


#pragma once

#include <string>

class Message
{
public:
    Message(const std::string& mesg);

    friend std::ostream& operator<<(std::ostream& os, Message& obj);
private:
    std::string m_message;

    std::ostream& printObject(std::ostream& os);
};