/*!
 *  \file       passing_arguments.cpp
 *  \brief
 *
 */


#include "passing_arguments.hpp"

#include <iostream>
#include <thread>
#include <cstdio>

#define UNUSED(arg)     (void)arg


void fn(int i, const std::string& str)
{
    UNUSED(i);
    UNUSED(str);
    std::cout << "called fn(int i, const std::string& str)" << std::endl;
}

void passPointerToThreadFunction(int some)
{
    char buffer[1024] = {0};
    std::snprintf(buffer, sizeof(buffer), "%i", some);
    std::thread task(fn, 3, std::string(buffer));   // 使用 std::string, 避免悬垂指针
    task.detach();
}

void updateDataForWidget(WidgetID wid, WidgetData& data)
{
    UNUSED(wid);
    UNUSED(data);
}

void displayStatus()
{
}

void processWidgetData(const WidgetData& data)
{
    UNUSED(data);
}

void passReferenceToThreadFunction(WidgetID wid)
{
    WidgetData data;
    std::thread task(updateDataForWidget, wid, std::ref(data));
    displayStatus();
    task.join();

    processWidgetData(data);
}

void XWorker::bomb()
{
    std::cout << "called XWorker::bomb() method" << std::endl;
}

void XWorker::fight(int num)
{
    std::cout << "called XWorker::fight(int num = " << num << ") method" << std::endl;
}

void XWorker::standby(XWorker::Location& stationary_location)
{
    stationary_location.xcoord += 15;   // 15km
    stationary_location.ycoord -= 28;   // 28km

    std::cout << "The army standby at the location(" << stationary_location.xcoord
              << ", " << stationary_location.ycoord << ")" << std::endl;
}

void passObjectMethodToThreadFunction()
{
    XWorker xman;
    std::thread bomb_task(&XWorker::bomb, &xman);
    bomb_task.join();

    XWorker iron_man;
    [[maybe_unused]] int num{10};
    std::thread fight_task(&XWorker::fight, &iron_man, num);
    fight_task.join();

    XWorker::Location navy_location{};
    std::thread station_task(&XWorker::standby, std::ref(navy_location));
    station_task.join();
}

void processBigObject(std::unique_ptr<BigObject> objptr)
{
    UNUSED(objptr);
}

BigObject::BigObject(unsigned length) : array{nullptr}
{
    array = new int[length];
    if (array == nullptr)
    {
        throw std::bad_alloc();
    }
}

BigObject::~BigObject()
{
    if (array != nullptr)
    {
        delete [] array;
    }
}

BigObject::BigObject(BigObject&& other)
{
    array = other.array;
    other.array = nullptr;
}

BigObject& BigObject::operator=(BigObject&& other)
{
    if (this != &other)
    {
        delete [] array;
        array = other.array;
        other.array = nullptr;
    }
    return *this;
}

void BigObject::prepareData(int num)
{
    array = static_cast<int*>(std::realloc(array, num));
    if (array == nullptr)
    {
        throw std::bad_alloc();
    }
}

void passMovableObjectToThreadFunction()
{
    std::unique_ptr<BigObject> p(new BigObject(0xFFFF));
    p->prepareData(42);

    std::thread move_task(processBigObject, std::move(p));
    move_task.join();
}
