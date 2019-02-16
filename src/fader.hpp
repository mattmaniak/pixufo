#ifndef FADER_HPP
#define FADER_HPP

#include <SDL2/SDL.h>

class Rendering;
class Menu;
class Level;
class Background;

class Fader
{
	const float max_time;
	float       beginning_time;
	float       elapsed_time;
	float       old_alpha;
	float       new_alpha;

	public:
	Fader();

	bool primary_menu_to_level(Rendering* Rendering, Menu* Menu, Level* Level);
	bool level_to_pause_menu();
	bool pause_menu_to_primary_menu();
};

#endif
