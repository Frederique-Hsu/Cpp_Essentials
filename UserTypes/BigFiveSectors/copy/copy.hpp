/*!
 *  \file       copy.hpp
 *  \brief
 *
 */


#pragma once

class Representation;
class Descriptor;

class Image
{
public:
    Image(Representation* repr, bool is_shared = true);
    Image(const Image& img);

private:
    Representation* m_rep;
    bool m_shared;

public:
    void write_block(Descriptor);

private:
    Representation* clone();
};