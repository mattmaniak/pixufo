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

	Keyboard();

	bool handle_ingame(Level* Level, Menu* Menu);
	bool handle_menu(Menu* Menu);
	bool handle_pause(Menu* Menu);
};

#endif
