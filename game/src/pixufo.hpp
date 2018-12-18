#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

namespace sdl_wrapper
{
	void init();
	SDL_Window* create_window();
	SDL_Surface* load_bitmap(std::string path);
	void set_icon(SDL_Window* window_to_set, std::string path);
}

int main();

#endif
