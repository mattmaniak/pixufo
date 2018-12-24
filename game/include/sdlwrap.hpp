#ifndef SDLWRAP_HPP
#define SDLWRAP_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

namespace sdlwrap
{
	SDL_Surface* load_bitmap(SDL_Window* window, std::string path);
	void         set_icon(SDL_Window* window_to_set, std::string path);
}

#endif
