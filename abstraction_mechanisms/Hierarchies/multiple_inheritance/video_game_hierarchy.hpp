/*!
 *  \file       video_game_hierarchy.hpp
 *  \brief      
 *  
 */


#pragma once


class Window
{
public:
    virtual void draw() = 0;    // 显示图像
};

class Cowboy
{
public:
    virtual void draw() = 0;    // 从枪套中拔枪
};

struct WWindow : public Window
{
    using Window::Window;
    
    virtual void win_draw() = 0;
    void draw() override final;
};

struct CCowboy : public Cowboy
{
    using Cowboy::Cowboy;
    
    virtual void cow_draw() = 0;
    void draw() override final;
};

class Cowboy_Window : public CCowboy, public WWindow
{
public:
    void cow_draw() override;
    void win_draw() override;
};