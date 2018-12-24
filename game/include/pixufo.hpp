#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <SDL2/SDL.h>
#include <iostream>

#define SCALE 4
#define RESIZE_SURFACE(surface) (surface->w * SCALE), (surface->h * SCALE)

class Game;

namespace sdl_wrapper
{
	extern void         init();
	extern SDL_Window*  create_window();
	extern SDL_Surface* load_bitmap(SDL_Window* window, std::string path);
	extern void         set_icon(SDL_Window* window, std::string path);
}

int main();

#endif
