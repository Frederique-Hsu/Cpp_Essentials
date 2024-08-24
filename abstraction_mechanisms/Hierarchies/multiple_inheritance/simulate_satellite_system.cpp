/*!
 *  \file       simulate_satellite_system.cpp
 *  \brief      
 *  
 */


#include "simulate_satellite_system.hpp"

#include <iostream>

class Position
{
public:
    Position(int x = 0, int y = 0);
private:
    int xcoord;
    int ycoord;
};

Position::Position(int x, int y) : xcoord{x}, ycoord{y}
{
}

void CommunicationSat::draw()
{
}

void CommunicationSat::transmit()
{
}

Position CommunicationSat::center() const
{
    return Position();
}

class DebugInfo
{
public:
    DebugInfo() = default;
};

static DebugInfo merge_info(DebugInfo a, DebugInfo b)
{
    return DebugInfo();
}

DebugInfo ISatellite::get_debug()
{
    std::cout << "called ISatellite::get_debug()" << std::endl;
    return DebugInfo();
}

DebugInfo IDisplayed::get_debug()
{
    std::cout << "called IDisplay::get_debug()" << std::endl;
    return DebugInfo();
}

DebugInfo CommunicationSat::get_debug()
{
    DebugInfo dbg_1 = ISatellite::get_debug();
    DebugInfo dbg_2 = IDisplayed::get_debug();
    
    return merge_info(dbg_1, dbg_2);
}

void Telstar::draw()
{
    CommunicationSat::draw();
    
    // ...
}