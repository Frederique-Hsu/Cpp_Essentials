/*!
 *  \file       Ival_box.cpp
 *  \brief      
 *  
 */


#include "Ival_box.hpp"

#if (INHERITANCE_WAY == IMPLEMENTATION_INHERITANCE)
    Ival_box::Ival_box(int low, int high) : m_val{low}, m_low{low}, m_high{high}
    {
    }

    Ival_box::~Ival_box()
    {
    }

    int Ival_box::get_value()
    {
        changed = false;
        return m_val;
    }

    void Ival_box::set_value(int val)
    {
        changed = true;
        m_val = val;
    }

    void Ival_box::reset_value(int val)
    {
        changed = false;
        m_val = val;
    }

    void Ival_box::prompt()
    {
    }

    bool Ival_box::was_changed() const
    {
        return changed;
    }
    
    void interact(Ival_box* pb)
    {
        pb->prompt();
        
        int value = pb->get_value();
        if (pb->was_changed())
        {
            // todo
        }
        else
        {
            // todo
        }
    }
#elif (INHERITANCE_WAY == INTERFACE_INHERITANCE)
#endif