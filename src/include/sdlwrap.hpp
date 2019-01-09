#ifndef SDLWRAP_HPP
#define SDLWRAP_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

namespace sdlwrap
{
	SDL_Surface* load_image(const std::string path);
}

#endif
