#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <limits>
#include <SDL2/SDL.h>

class Model_player;
class Pause;
class Menu;

class Keyboard
{
	public:
	SDL_Event    event;
	const Uint8* keys;
	Uint8        keys_amount;

	Keyboard();

	bool handle_ingame(Model_player* Player, bool* pause_active);
	bool handle_menu(Menu* Menu);
	bool handle_pause(Menu* Menu, Pause* Pause);
};

#endif
