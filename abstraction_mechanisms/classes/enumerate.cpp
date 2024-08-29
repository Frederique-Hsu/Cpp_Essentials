/*!
 *  \file   enumerate.cpp
 *  \brief  talk about the user-defined enum type.
 *  
 */

enum class Color
{
    red,
    blue,
    gree
};

enum class Traffic_Light
{
    green,
    yellow,
    red
};

Traffic_Light& operator++(Traffic_Light& t)
{
    switch (t)
    {
    case Traffic_Light::green:
        return t = Traffic_Light::yellow;
    case Traffic_Light::yellow:
        return t = Traffic_Light::red;
    case Traffic_Light::red:
        return t = Traffic_Light::green;
    default:
        return t = Traffic_Light::green;
    }
}

#if 0
Color color = Color::red;
Traffic_Light light = Traffic_Light::red;
Traffic_Light next = ++light;

// Color x = red;      // Error, 'red' was not declared in the Color scope.
// Color y = Traffic_Light::red;   // Error: cannot convert 'Traffic_Light' to 'Color' in initialization
Color z = Color::red;

// int i = Color::red;     // Error: Color::red is not the int type
// Color c = 2;    // Error: 2 is not an object of Color
#endif