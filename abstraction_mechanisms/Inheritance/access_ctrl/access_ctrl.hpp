/*!
 *  \file       access_ctrl.hpp
 *  \brief      
 *  
 */


#pragma once

class Buffer
{
public:
    char& operator[](int index);    // this function will check the accessing member
protected:
    char& access(int index);        // this function will not check

protected:
    char a[128];
};

class CircularBuffer : public Buffer
{
public:
    void reallocate(char* p, int s);
};

class LinkedBuffer : public Buffer
{
};