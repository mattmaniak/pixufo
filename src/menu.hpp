#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <vector>

#include "background.hpp"
#include "button.hpp"

class Keyboard;
class Graphics;
class Level;

class Menu
{
	public:
	enum
	{
		primary_enabled,
		pause_enabled,
		all_disabled
	}
	mode;

	unsigned int         max_button_idx;
	unsigned int         selected_button_idx;
	std::vector<Button*> Buttons;
	Background*          Space_bg;

	Menu();

	bool primary(Graphics* Graphics, Keyboard* Keyboard);
	bool pause(Graphics* Graphics, Keyboard* Keyboard, Level* Level);
};

#endif
