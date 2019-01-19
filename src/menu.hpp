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

	Menu();

	bool primal(Game* Pixufo, Graphics* Graphics);
	bool paused(Game* Pixufo, Graphics* Graphics);
	void handle_keyboard(Game* Pixufo);
	bool render();
};

class Button: public Model
{
	public:
	int index;

	Button(Graphics* Graphics, const std::string name, const int idx);

	bool render(Graphics* Graphics, Menu* Menu);
};

#endif
