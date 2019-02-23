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
	Keyboard();

	bool move_player(Level* Level, Menu* Menu, Graphics* Graphics);
	bool menu(Menu* Menu);
	bool pause(Menu* Menu);

	private:
	SDL_Event    Event;
	const Uint8* keys;
	std::size_t  pressed_keys_amount;

	void count_keys();

};

#endif
