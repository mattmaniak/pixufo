#ifndef MENUS_HPP
#define MENUS_HPP

#include <map>
#include <SDL2/SDL.h>
#include <vector>
#include "error.hpp"
#include "scene.hpp"
#include "button.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"

class Level;
class Player;

class New_menu: public Scene
{
public:
	bool is_initialized;

	enum
	{
		primary_enabled,
		pause_enabled,
		all_disabled
	}
	mode;

	std::size_t                   selected_button_idx;
	std::vector<Button*>           Buttons;
	std::map<std::string, Sprite*> Sprites;

	New_menu(Graphics&);
	~New_menu();

	virtual bool keyboard_steering() = 0;
	virtual bool render()            = 0;
};


class Main_menu: public New_menu
{
public:
	bool keyboard_steering();
	bool render();
};

class Pause_menu: public New_menu
{
public:
	bool keyboard_steering();
	bool render();
};

class Menu: public Scene
{
public:
	enum
	{
		primary_enabled,
		pause_enabled,
		all_disabled
	}
	mode;

	Sprite*              Select_arrow;
	Sprite*              Logo;
	unsigned int         selected_button_idx;
	std::vector<Button*> Buttons;

	Menu(Graphics&);
	~Menu();

	bool primary(Graphics&, Keyboard&);
	bool pause(Graphics&, Keyboard&, Level&);
};

#endif
