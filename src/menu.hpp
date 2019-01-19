#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>

class Game;
class Model;
class Graphics;

class Menu
{
	public:
	int max_button_index;
	int current_button_index;

	bool primal(Game* Pixufo, Graphics* Graphics);
	bool pause(Game* Pixufo, Graphics* Graphics);
	void handle_keyboard(Game* Pixufo);
};

class Button: public Model
{
	public:
	int index;

	Button(Graphics* Graphics, const std::string name, const int idx);

	bool render(Graphics* Graphics, Menu* Menu);
};

#endif
