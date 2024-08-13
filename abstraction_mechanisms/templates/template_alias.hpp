/*!
 *  \file       template_alias.hpp
 *  \brief      
 *  
 */


#pragma once

#include <vector>
#include <string>

/* Declaration ===================================================================================*/
template<typename Container>
using Element_Type = typename Container::value_type;

template<typename Container> void algo(Container& container);

template<typename Key, typename Value> class Map;
template<typename Value>
using String_map = Map<std::string, Value>;


/* Implementation ================================================================================*/
template<typename Container> void algo(Container& container)
{
    std::vector<Element_Type<Container>> vec;
}

String_map<int> m;      // m是一个Map<std::string, int>