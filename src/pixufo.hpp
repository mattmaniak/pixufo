#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include "error.hpp"
#include "font.hpp"
#include "graphics.hpp"
#include "sprite.hpp"
#include "menu.hpp"
#include "level.hpp"
#include "player.hpp"
#include "states.hpp"

class Game
{
public:
    states state;

    Game();
    ~Game();

    bool level_loop();
    bool main_menu_loop();
    bool credits_menu_loop();
    bool pause_menu_loop();

private:
    Graphics* Graphics_;
    Level*    Level_;
};

#endif
