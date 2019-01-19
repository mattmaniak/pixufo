#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>

class Game;
class Graphics;

class Button // TODO: INHERIT FROM MODEL?
{
	public:
	bool         initialized;
	bool         selected;
	SDL_Texture* Texture;
	int          pos_x;
	int          pos_y;

	Button();
	~Button();
};

class Menu
{
	public:
	bool main(Game* Pixufo, Graphics* Graphics);
	bool paused(Game* Pixufo, Graphics* Graphics);
	bool render();
};

#endif
