/*!
 *  \file       Ival.cpp
 *  \brief      
 *  
 */


#include "Ival.hpp"


#if (INHERITANCE_WAY == IMPLEMENTATION_INHERITANCE)
    Ival_slider::Ival_slider(int low, int high, int slider) : Ival_box(low, high), m_slider{slider}
    {
    }

    Ival_slider::~Ival_slider()
    {
    }
    
    int Ival_slider::get_value()
    {
        changed = false;
        return m_val;
    }
    
    void Ival_slider::prompt()
    {
    }
#elif (INHERITANCE_WAY == INTERFACE_INHERITANCE)
#endif