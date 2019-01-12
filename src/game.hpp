#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

class Game
{

	public:
	SDL_Event event;
	bool      running;

	Game();
	~Game();

	void handle_keyboard();
	void loop();
	void quit();
};

#endif
