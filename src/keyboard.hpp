#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cmath>
#include <limits>
#include <SDL2/SDL.h>

class Menus;

class Keyboard
{
public:
	bool menu(Menus&);
	bool pause(Menus&);

private:
	SDL_Event    Event;
};

#endif
