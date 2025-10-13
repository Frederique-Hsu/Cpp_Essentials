/*!
 *  \file       passing_arguments.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

void fn(int i, const std::string& str);

void passPointerToThreadFunction(int some);

using WidgetID = unsigned;

struct WidgetData
{
};

void passReferenceToThreadFunction(WidgetID wid);

class XWorker
{
public:
    struct Location
    {
        int xcoord;
        int ycoord;
    };

    static void standby(Location& stationary_location);
public:
    void bomb();
    void fight(int num);
};

void passObjectMethodToThreadFunction();

class BigObject
{
public:
    explicit BigObject(unsigned length);
    ~BigObject();
    BigObject(BigObject&& other);
    BigObject& operator=(BigObject&& other);

public:
    void prepareData(int num);

private:
    int *array;
};

void passMovableObjectToThreadFunction();
