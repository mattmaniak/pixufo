#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cmath>
#include <limits>
#include <SDL2/SDL.h>

class Player;
class Pause;
class Menu;
class Rendering;
class Level;

class Keyboard
{
	public:
	SDL_Event    Event;
	const Uint8* keys;
	int          keys_amount;
	SDL_Scancode last_key;

	Keyboard();

	bool move_player(Level* Level, Menu* Menu);
	void levitate_diagonally(Level* Level, SDL_Scancode key);
	void count_keys();
	bool menu(Menu* Menu);
	bool pause(Menu* Menu);
};

#endif
