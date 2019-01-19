#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>

class Game;
class Model;
class Graphics;

class Menu
{
	public:
	bool primal(Game* Pixufo, Graphics* Graphics);
	bool paused(Game* Pixufo, Graphics* Graphics);
	bool render();
};

class Button: public Model
{
	public:
	int  index;
	bool selected;

	Button(Graphics* Graphics, const std::string name, const int idx,
	       const bool select);

	bool render(Graphics* Graphics);
};

#endif
