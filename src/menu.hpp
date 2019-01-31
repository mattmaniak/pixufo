#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <vector>

class Keyboard;
class Graphics;

namespace model
{
	class Button;
}


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

	size_t                      max_button_index;
	size_t                      current_button_index;
	std::vector<model::Button*> Buttons;

	Menu();

	bool primary(Graphics* Graphics, Keyboard* Keyboard);
	bool pause(Graphics* Graphics, Keyboard* Keyboard);
};

#endif
