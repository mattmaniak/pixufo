#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <limits>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

#define MIN_RESOLUTION_W 1280
#define MIN_RESOLUTION_H 720

class Game
{
	void _error(const std::string message);

	public:
	SDL_Event       event;
	SDL_DisplayMode display;
	SDL_Window*     window;
	SDL_Renderer*   renderer;
	double          delta_time; // Single frame's time in seconds.

	Game();
	~Game();

	SDL_Surface* load_image(const std::string path);
	SDL_Texture* create_texture(SDL_Surface* image);
	void         loop();
	void         keyboard();
	void         quit();

};

#endif
