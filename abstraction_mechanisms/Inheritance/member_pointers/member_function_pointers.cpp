/*!
 *  \file       member_function_pointers.cpp
 *  \brief      
 *  
 */


#include "member_function_pointers.hpp"

void (*pfn)() = &Task::schedule;                // OK
// void (Task::* pmember_fn)() = &Task::schedule;  // error: ordinary pointer assigned to pointer to member.

void suspend(StdInterface* pinterface)
{
    pointer_to_member_function suspend = &StdInterface::suspend;

    // pinterface->suspend();
    (pinterface->*suspend)();
}

void LaunchAction::start()
{
    std::cout << "execute the start action" << std::endl;
}

void QuitAction::quit()
{
    std::cout << "execute the quit action" << std::endl;
}

void ScheduleAction::suspend()
{
    std::cout << "execute the suspend action" << std::endl;
}

void ScheduleAction::resume()
{
    std::cout << "execute the resume action" << std::endl;
}

Interpreter::Interpreter()
{
    using namespace std;

    operation = map<string, pointer_to_member_function>{{"start",       &StdInterface::start},
                                                        {"suspend",     &StdInterface::suspend},
                                                        {"resume",      &StdInterface::resume},
                                                        {"quit",        &StdInterface::quit}};

    variable = map<string, std::shared_ptr<StdInterface>>{
        {"launch",    std::make_shared<LaunchAction>()},
        {"quit",      std::make_shared<QuitAction>()},
        {"suspend",   std::make_shared<ScheduleAction>()},
        {"resume",    std::make_shared<ScheduleAction>()}
    };
}

void Interpreter::call_member(std::string var, std::string oper)
{
    auto pobj = variable[var].get();
    auto method = operation[oper];

    (pobj->*method)();
}

void Task::schedule()
{
}