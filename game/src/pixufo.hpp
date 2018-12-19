#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <SDL2/SDL.h>
#include <iostream>

#define STRETCH_BITMAP(bitmap) bitmap->w * 4, bitmap->h * 4

namespace sdl_wrapper
{
	extern void init();
	extern SDL_Window* create_window();
	extern SDL_Surface* load_bitmap(SDL_Window* window, std::string path);
	extern void set_icon(SDL_Window* window, std::string path);
}

int main();

#endif
