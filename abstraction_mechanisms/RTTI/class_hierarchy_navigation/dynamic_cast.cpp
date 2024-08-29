/*!
 *  \file       dynamic_cast.cpp
 *  \brief
 *
 */


#include "dynamic_cast.hpp"


Ival_slider::Ival_slider()
{
}

Ival_slider::~Ival_slider()
{
}

BBslider::BBslider() : BBwindow()
{
}

BBslider::~BBslider()
{
}

BB_ival_slider::BB_ival_slider() : Ival_slider(), BBslider()
{
}

BB_ival_slider::~BB_ival_slider()
{
}

int BB_ival_slider::get_value() const
{
    return int{};
}

BBdial::BBdial(int scale_mark) : BBwindow(), m_scale{scale_mark}
{
}

BB_ival_dial::BB_ival_dial(int scale_mark) : Ival_box(), BBdial(scale_mark)
{
}

int BB_ival_dial::get_value() const
{
    return 10;
}

int BB_ival_dial::getDialScale() const
{
    return m_scale;
}


void my_event_handler(BBwindow* pwind)
{
    if (auto pbox = dynamic_cast<Ival_box*>(pwind))
    {
        int value = pbox->get_value();
    }
    else
    {
    }
}