/*!
 *  \file       Cat.hpp
 *  \brief
 *
 */


#include "Animal.hpp"


class Cat final : public Animal
{
public:
    Cat(const std::string& name);

private:
    std::string name_impl() const override;
};
