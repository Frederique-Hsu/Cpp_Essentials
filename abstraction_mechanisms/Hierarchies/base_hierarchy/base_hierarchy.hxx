/*!
 *  \file       base_hierarchy.hxx
 *  \brief      
 *  
 */


#pragma once

#include <string>

class Storable
{
public:
    Storable(const std::string& str);
    virtual ~Storable() {}
    
    Storable(const Storable&) = delete;
    Storable& operator=(const Storable&) = delete;
    
protected:
    std::string file_name;
    
public:
    virtual std::string get_file() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
};

class Transmitter : public virtual Storable
{
public:
    Transmitter(const std::string& filename = "");
    virtual ~Transmitter() = default;
    
public:
    void write() override;
};

class Receiver : public virtual Storable
{
public:
    Receiver(const std::string& filename = "");
    virtual ~Receiver() = default;
    
public:
    void write() override;
};

class Radio : public Transmitter, public Receiver
{
public:
    Radio(const std::string& filename);
    ~Radio() = default;
    
public:
    std::string get_file() override;
    void write() override;
    void read() override;
};