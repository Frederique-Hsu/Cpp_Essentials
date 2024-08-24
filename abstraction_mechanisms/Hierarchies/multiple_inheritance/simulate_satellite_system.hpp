/*!
 *  \file       simulate_satellite_system.hpp
 *  \brief      
 *  
 */


#pragma once

class Position;
class DebugInfo;

class SimObj
{
public:
};

class Widget
{
public:
};

class ISatellite : public SimObj
{
public:
    virtual Position center() const = 0;
    
    virtual DebugInfo get_debug();
};

class IDisplayed : public Widget
{
public:
    virtual void draw() = 0;
    
    virtual DebugInfo get_debug();
};

class CommunicationSat : public ISatellite, public IDisplayed
{
public:
    void transmit();
    
    Position center() const override;
    void draw() override;
    
    DebugInfo get_debug() override;
};

void highlight(IDisplayed*);
Position center_of_gravity(const ISatellite*);

class Telstar : public CommunicationSat
{
public:
    void draw();
};