/*!
 *  \file       background_work.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

void doBackgroundWork();

void editDocument(std::string const& filename);

enum class CommandType
{
    OPEN_NEW_DOCUMENT
};

struct UserCommand
{
    CommandType type;

    UserCommand() : type{CommandType::OPEN_NEW_DOCUMENT}
    {
    }
};
