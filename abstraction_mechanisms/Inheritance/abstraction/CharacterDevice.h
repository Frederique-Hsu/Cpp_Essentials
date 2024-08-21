/*!
 *  \file       CharacterDevice.h
 *  \brief      
 *  
 */


#pragma once

#define interface   struct

interface CharacterDevice
{
    virtual ~CharacterDevice() = default;

    virtual int open(int opt) = 0;
    virtual int close(int opt) = 0;
    virtual int read(char* p, int n) = 0;
    virtual int write(const char* p, int n) = 0;
    virtual int ioctl(int ...) = 0;
};