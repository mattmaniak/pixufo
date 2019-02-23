#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#define SDL2_SUCCESS 0

namespace error
{
	void show_box(const std::string);
}

#endif
