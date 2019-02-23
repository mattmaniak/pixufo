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

	Model*               Select_arrow;
	Background*          Space_bg;
	Model*               Logo;
	unsigned int         max_button_idx;
	unsigned int         selected_button_idx;
	std::vector<Button*> Buttons;

	Menu();

	bool primary(Graphics*, Keyboard*);
	bool pause(Graphics*, Keyboard*, Level*);
};

#endif
