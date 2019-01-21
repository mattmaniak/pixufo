#ifndef MENUS_HPP
#define MENUS_HPP

#include <SDL2/SDL.h>

class Keyboard;
class Graphics;

class Menu
{
	public:
	bool         active;
	unsigned int max_button_index;
	unsigned int current_button_index;

	Menu();

	bool launch(Graphics* Graphics, Keyboard* Keyboard);
};

#endif
