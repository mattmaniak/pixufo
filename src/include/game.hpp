#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

#define MIN_RESOLUTION_W 1280
#define MIN_RESOLUTION_H 720

class Game
{
	void _error(const std::string message);

	public:
	bool      running;
	SDL_Event event;

	Game();
	~Game();

	void         loop();
	void         quit();
};

#endif
