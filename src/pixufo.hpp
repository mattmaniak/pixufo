#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include "error.hpp"
#include "font.hpp"
#include "graphics.hpp"
#include "sprite.hpp"
#include "menu.hpp"
#include "keyboard.hpp"
#include "level.hpp"
#include "player.hpp"

class Game
{
public:
	Game();
	~Game();

	void loop();

private:
	Graphics* Graphics_;
	Menu*     Menu_;
	Keyboard* Keyboard_;
	Level*    Cosmic_;
};

#endif
