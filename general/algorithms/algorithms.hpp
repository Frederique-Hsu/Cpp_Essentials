/*!
 *  \file       algorithms.hpp
 *  \brief
 *
 */


#pragma once

#include "phone_book.hpp"

#include <vector>
#include <list>

void unique_sort_copy(std::vector<Entry>& vec, std::list<Entry>& lst);
std::list<Entry> unique_sort_append(std::vector<Entry>& vec);
