/*!
 *  \file       multiple_inheritances_casting.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

#define interface   struct

interface IStorable
{
    virtual ~IStorable() = default;

    virtual std::string read() = 0;
    virtual void write(const std::string& msg) = 0;
};

class Component : public virtual IStorable
{
public:
    virtual ~Component() = default;
public:
    virtual void communicate();
};

class Receiver : public Component
{
public:
    Receiver();
    virtual ~Receiver();
public:
    std::string read() override;
};

class Transmitter : public Component
{
public:
    Transmitter(const std::string& msg);
    virtual ~Transmitter();
private:
    std::string m_msg;
public:
    void write(const std::string& msg) override;
};

class Radio : public Receiver, public Transmitter
{
public:
    Radio(const std::string& message);
    ~Radio();
public:
    void communicate() override;
};

void cast(Radio& ref_radio);
void cast(IStorable* ptr_store);
