/*!
 *  \file       test.my.vector.c++
 *  \brief
 *
 */


#include "test.my.vector.h++"

#include "my.vector.hpp"

void UTester4MyVector::SetUp()
{
}

void UTester4MyVector::TearDown()
{
}

TEST_F(UTester4MyVector, CheckMyVectorBase)
{
    my::vector_base<int> vibase(std::allocator<int>(), 8);

    EXPECT_EQ(typeid(vibase.alloc), typeid(std::allocator<int>));
    EXPECT_NE(vibase.elem, nullptr);

    auto length = vibase.last - vibase.elem;
    EXPECT_EQ(length, 8);
    EXPECT_EQ(vibase.space - vibase.elem, 8);
    EXPECT_EQ(vibase.space, vibase.last);

    // my::vector_base<int> vicopy(vibase);    // Error: no copy constructor
    // my::vector_base<int> viassign = vibase;     // Error: no copy assignment operator

    my::vector_base<int> vimove(my::vector_base<int>(std::allocator<int>(), 20));
    EXPECT_EQ(vimove.last - vimove.elem, 20);

    my::vector_base<int> vi_move_assinger = std::move(vibase);
    EXPECT_EQ(vi_move_assinger.last - vi_move_assinger.elem, 8);
    EXPECT_EQ(vibase.elem, nullptr);
}

TEST_F(UTester4MyVector, CheckVectorConstruction)
{
    my::vector<int> vec(15);
}
