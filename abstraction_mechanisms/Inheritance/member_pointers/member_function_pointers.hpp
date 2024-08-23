/*!
 *  \file       member_function_pointers.hpp
 *  \brief      
 *  
 */


#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>

class StdInterface
{
public:
    virtual ~StdInterface() = default;
    
public:
    virtual void start() = 0;
    virtual void suspend() = 0;
    virtual void resume() = 0;
    virtual void quit() = 0;
    virtual void full_size() = 0;
    virtual void small() = 0;
};

class LaunchAction : public StdInterface
{
public:
    void start() override;
private:
    void suspend() override {}
    void resume() override {}
    void quit() override {}
    void full_size() override {}
    void small() override {}
};

class QuitAction : public StdInterface
{
public:
    void quit() override;
private:
    void start() override { std::cout << "Cannot execute the start action" << std::endl; }
    void suspend() override {}
    void resume() override {}
    void full_size() override {}
    void small() override {}
};

class ScheduleAction : public StdInterface
{
public:
    void suspend() override;
    void resume() override;
private:
    void start() override {}
    void quit() override {}
    void full_size() override {}
    void small() override {}
};

using pointer_to_member_function = void (StdInterface::*)();

void suspend(StdInterface* pinterface);

class Interpreter
{
public:
    Interpreter();

private:
    std::map<std::string, std::shared_ptr<StdInterface>> variable;
    std::map<std::string, pointer_to_member_function> operation;

public:
    void call_member(std::string var, std::string oper);
};

class Task
{
public:
    static void schedule();
};

