/*!
 *  \file       background_work.cpp
 *  \brief
 *
 */


#include "background_work.hpp"

#include <thread>

#define UNUSED(arg)     (void)arg

void doBackgroundWork()
{
}

void openDocument_DisplayGUI(const std::string& filename)
{
    UNUSED(filename);
}

bool doneEditing()
{
    return true;
}

UserCommand getUserInput()
{
    return UserCommand();
}

std::string getFilenameFromUser()
{
    return std::string("foo.doc");
}

void processUserInput(const UserCommand& cmd)
{
    UNUSED(cmd);
}

void editDocument(std::string const& filename)
{
    openDocument_DisplayGUI(filename);
    while (!doneEditing())
    {
        UserCommand cmd = getUserInput();
        if (cmd.type == CommandType::OPEN_NEW_DOCUMENT)
        {
            std::string const new_name = getFilenameFromUser();
            std::thread task(editDocument, new_name);
            task.detach();
        }
        else
        {
            processUserInput(cmd);
        }
    }
}
