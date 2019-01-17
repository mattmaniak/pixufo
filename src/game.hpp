#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

class Model;
class Graphics;

class Game
{
	public:
	SDL_Event event;
	bool      running;

	Game();
	~Game();

	void handle_keyboard(Model* Player, const Uint8* key);
};

#endif
