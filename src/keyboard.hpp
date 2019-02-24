#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cmath>
#include <limits>
#include <SDL2/SDL.h>

class Player;
class Menu;
class Graphics;

class Keyboard
{
	public:
	Keyboard();

	bool move_player(Player*, Menu*, Graphics*);
	bool menu(Menu*);
	bool pause(Menu*);

	private:
	SDL_Event    Event;
	const Uint8* keys;
};

#endif
