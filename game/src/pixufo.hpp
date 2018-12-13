#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <iostream>
#include <SDL2/SDL.h>

namespace sdl_wrapper
{
	void         init();
	SDL_Window*  create_window();
	SDL_Surface* load_bitmap(const char* path);
}

int main();

#endif
