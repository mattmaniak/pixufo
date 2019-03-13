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

class Menu: public Scene
{
public:
	std::vector<Button*>           Buttons;
	std::map<std::string, Sprite*> Sprites;

	Menu(Graphics&);
	~Menu();

	virtual bool keyboard_steering() = 0;
	virtual bool render()            = 0;
};


class Main_menu: public Menu
{
public:
	bool keyboard_steering();
	bool render();
};

class Pause_menu: public Menu
{
public:
	bool keyboard_steering();
	bool render();
};

class Menus: public Scene
{
public:
	enum
	{
		primary_enabled,
		pause_enabled,
		all_disabled
	}
	mode;

	std::size_t         selected_button_idx;

	Sprite*                        Select_arrow;
	std::map<std::string, Sprite*> Sprites;

	Sprite*              Logo;
	std::vector<Button*> Buttons;

	Menus(Graphics&);
	~Menus();

	bool primary(Graphics&, Keyboard&);
	bool pause(Graphics&, Keyboard&, Level&);
};

#endif
