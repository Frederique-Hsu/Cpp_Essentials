/*!
 *  \file       Ival.hpp
 *  \brief      
 *  
 */


#pragma once

#include "Ival_box.hpp"


#if (INHERITANCE_WAY == IMPLEMENTATION_INHERITANCE)
    class Ival_slider : public Ival_box
    {
    private:
        int m_slider;
        
    public:
        Ival_slider(int low, int high, int slider);
        ~Ival_slider();
        
    public:
        int get_value() override;
        void prompt() override;
    };
    
    class Ival_dial : public Ival_box
    {
    };
    
    class Flashing_ival_slider : public Ival_slider
    {
    };
    
    class Popup_ival_slider : public Ival_slider
    {
    };
#elif (INHERITANCE_WAY == INTERFACE_INHERITANCE)
    class Ival_slider : public Ival_box, protected BBwidget
    {
    public:
        Ival_slider(int, int);
        ~Ival_slider() override;
    
    protected:
        void draw() override;
        
    private:
        int m_slider;
        
    public:
        int get_value() override;
        void set_value(int val) override;
    };
    
    class Ival_dial : public Ival_box, protected BBwidget
    {
    public:
        Ival_dial(int, int);
        ~Ival_dial() override;
        
    protected:
        void draw() override;
        
    public:
        void prompt() override;
        bool was_changed() const override;
    };
    
    class Flashing_ival_slider : public Ival_slider
    {
    public:
        Flashing_ival_slider();
        ~Flashing_ival_slider();
    };
    
    class Popup_ival_slider : public Ival_slider
    {
    public:
        Popup_ival_slider();
        ~Popup_ival_slider();
    };
    
    class Ival_maker
    {
    public:
        virtual Ival_dial* dial(int, int) = 0;
        virtual Popup_ival_slider* popup_slider(int, int) = 0;
    };
    
    class BB_maker : public Ival_maker
    {
    public:
        Ival_dial* dial(int, int) override;
        Popup_ival_slider* popup_slider(int, int) override;
    };
    
    class LS_maker : public Ival_maker
    {
    public:
        Ival_dial* dial(int, int) override;
        Popup_ival_slider* popup_slider(int, int) override;
    };
#else
    class Ival_slider : public Ival_box
    {
    };
    
    class BBslider : public BBwidget
    {
    };
    
    class CWslider : public CWwidget
    {
    };
    
    class BB_ival_slider : public Ival_slider, protected BBslider
    {
    };
    
    class CW_ival_slider : public Ival_slider, protected CWslider
    {
    };
#endif