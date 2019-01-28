#ifndef MENUS_HPP
#define MENUS_HPP

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
	bool                        initialized;
	bool                        active;
	size_t                      max_button_index;
	size_t                      current_button_index;
	std::vector<model::Button*> Buttons;

	Menu(Graphics* Graphics);
	~Menu();

	bool launch(Graphics* Graphics, Keyboard* Keyboard);
};

#endif
