#ifndef GAME_HPP
#define GAME_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

class Player;

class Game
{
	public:
	bool      running;
	bool      menu;
	bool      pause;
	SDL_Event event;

	Game();
	~Game();

	void handle_keyboard(Player* Player);
};

#endif
