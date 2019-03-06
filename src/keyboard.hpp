#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cmath>
#include <limits>
#include <SDL2/SDL.h>

class Menu;

class Keyboard
{
public:
	bool menu(Menu&);
	bool pause(Menu&);

private:
	SDL_Event    Event;
};

#endif
