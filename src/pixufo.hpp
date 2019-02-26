#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include "error.hpp"
#include "font.hpp"
#include "graphics.hpp"
#include "model.hpp"
#include "menu.hpp"
#include "keyboard.hpp"
#include "level.hpp"
#include "player.hpp"
#include "physics.hpp"

class Game
{
	public:
	bool is_initialized;

	Graphics* Gfx;
	Menu*     Menus;
	Keyboard* Kboard;
	Level*    Cosmic;

	bool loop();

	Game();
	~Game();
};

#endif
