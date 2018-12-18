#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <SDL2/SDL.h>
#include <iostream>

namespace sdl_wrapper
{
	extern void init();
	extern SDL_Window* create_window();
	extern SDL_Surface* load_bitmap(std::string path);
	extern void set_icon(SDL_Window* window_to_set, std::string path);
}

int main();

#endif
