/*!
 *  \file       dynamic_cast.hpp
 *  \brief
 *
 */


#pragma once

#define interface   struct


interface Ival_box
{
    virtual ~Ival_box() = default;

    virtual int get_value() const = 0;
};

class BBwindow
{
public:
    virtual ~BBwindow() = default;
};

class Ival_slider : public Ival_box
{
public:
    Ival_slider();
    virtual ~Ival_slider();
};

class BBslider : public BBwindow
{
public:
    BBslider();
    virtual ~BBslider();
};

class BBdial : public BBwindow
{
public:
    BBdial(int scale_mark);
    ~BBdial() = default;
protected:
    int m_scale;
};

class BB_ival_slider : public Ival_slider, protected BBslider
{
public:
    BB_ival_slider();
    ~BB_ival_slider();

public:
    int get_value() const override;
};

class BB_ival_dial : public Ival_box, protected BBdial
{
public:
    BB_ival_dial(int scale_mark);
    ~BB_ival_dial() = default;
public:
    int get_value() const override;
    int getDialScale() const;
};

void my_event_handler(BBwindow* pwind);
