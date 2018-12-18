#ifndef SDL_WRAPPER_HPP
#define SDL_WRAPPER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

namespace sdl_wrapper
{
	void init();
	SDL_Window* create_window();
	SDL_Surface* load_bitmap(std::string path);
	void set_icon(SDL_Window* window_to_set, std::string path);
}

#endif
