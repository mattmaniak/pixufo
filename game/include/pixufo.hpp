#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include <SDL2/SDL.h>
#include <iostream>

#define SUCCESS 0

#define FPS          60
#define FRAME_DELAY  (1000 / FPS)
#define SCALE_FACTOR 4

class Game;

namespace sdlwrap
{
	extern SDL_Surface* load_image(SDL_Window* window, std::string path);
}

int main();

#endif
