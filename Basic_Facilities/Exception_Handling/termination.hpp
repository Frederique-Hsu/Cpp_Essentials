/*!
 *  \file       termination.hpp
 *  \brief
 *
 */


#pragma once

using terminate_handler = void (*)();

[[noreturn]] void my_handler();

void dangerous();

int main_fn();
