#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <SDL2/SDL.h>
#include <iostream>

#define SUCCESS 0

#define SCALE 4
#define RESIZE_SURFACE(surface) (surface->w * SCALE), (surface->h * SCALE)

class Game;

namespace sdlwrap
{
	extern SDL_Surface* load_bitmap(SDL_Window* window, std::string path);
	extern void         set_icon(SDL_Window* window, std::string path);
}

int main();

#endif
