#ifndef PAUSE_HPP
#define PAUSE_HPP

#include <iostream>
#include <SDL2/SDL.h>

class Keyboard;
class Graphics;
class Menu;

class Pause // TODO: INHERIT FROM THE MENU.
{
	public:
	bool         active;
	unsigned int max_button_index;
	unsigned int current_button_index;

	Pause();
	bool launch(Graphics* Graphics, Keyboard* Keyboard, Menu* Menu);
};

#endif
