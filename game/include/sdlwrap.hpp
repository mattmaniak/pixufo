#ifndef SDLWRAP_HPP
#define SDLWRAP_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

namespace sdlwrap
{
	SDL_Surface* load_image(SDL_Window* window, std::string path);
}

#endif
