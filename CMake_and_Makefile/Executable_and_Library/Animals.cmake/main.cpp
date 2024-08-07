/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <cstdlib>
#include <memory>
#include <functional>
#include <iostream>

#include "Animal.hpp"
#include "Factory.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

typedef std::function<std::unique_ptr<Animal>(const std::string&)> CreateAnimal;

int main(int argc, char** argv)
{
    Factory<CreateAnimal> farm;
    farm.subscribe("CAT", [](const std::string& name) { return std::make_unique<Cat>(name); });
    farm.subscribe("DOG", [](const std::string& name) { return std::make_unique<Dog>(name); });

    auto simon = farm.create("CAT", "Simon");
    std::unique_ptr<Animal> marlowe = farm.create("DOG", "Marlowe");

    std::cout << simon->name() << std::endl;
    std::cout << marlowe->name() << std::endl;

    return EXIT_SUCCESS;
}