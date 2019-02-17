#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cmath>
#include <limits>
#include <SDL2/SDL.h>

class Player;
class Menu;
class Graphics;
class Level;

class Keyboard
{
	public:
	SDL_Event    Event;
	const Uint8* keys;
	size_t       pressed_keys_amount;

	Keyboard();

	void count_keys();
	bool move_player(Level* Level, Menu* Menu);
	bool menu(Menu* Menu);
	bool pause(Menu* Menu);
};

#endif
