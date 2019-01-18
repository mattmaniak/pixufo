#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>

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
	bool main(SDL_Renderer* Renderer);
	bool paused(SDL_Renderer* Renderer);
};

#endif
