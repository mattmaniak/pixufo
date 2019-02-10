#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <vector>

class Button;
class Keyboard;
class Rendering;

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

	Menu();

	bool primary(Rendering* Rendering, Keyboard* Keyboard);
	bool pause(Rendering* Rendering, Keyboard* Keyboard);
};

#endif
