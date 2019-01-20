#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>

class Game;
class Model;
class Graphics;
class Player;

class Menu
{
	public:
	unsigned int max_button_index;
	unsigned int current_button_index;

	bool primal(Game* Game, Graphics* Graphics);
	bool pause(Game* Game, Graphics* Graphics);
	void handle_keyboard(Game* Game);
	bool fader(Graphics* Graphics);
};

class Button: public Model
{
	public:
	unsigned int index;

	Button(Graphics* Graphics, const std::string name, const int idx);

	bool render(Graphics* Graphics, Menu* Menu);
};

#endif
