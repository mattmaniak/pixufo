#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cmath>
#include <limits>
#include <SDL2/SDL.h>

namespace model
{
	class Player;
}

class Pause;
class Menu;
class Graphics;
class Level;

class Keyboard
{
	public:
	SDL_Event    Event;
	const Uint8* keys;
	int          keys_amount;
	SDL_Scancode last_key;

	Keyboard();

	bool handle_ingame(Level* Level, Menu* Menu);
	void levitate_diagonally(Level* Level, SDL_Scancode key);
	void count_keys();
	bool handle_menu(Menu* Menu);
	bool handle_pause(Menu* Menu);
};

#endif
