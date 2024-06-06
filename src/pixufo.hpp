#ifndef PIXUFO_HPP
#define PIXUFO_HPP

#include "error.hpp"
#include "font.hpp"
#include "graphics.hpp"
#include "sprite.hpp"
#include "menu.hpp"
#include "level.hpp"
#include "player.hpp"
#include "state.hpp"

class Game
{
public:

    Game();
    ~Game();

    State get_state();

    bool level_loop();
    bool main_menu_loop();
    bool credits_menu_loop();
    bool pause_menu_loop();


private:
    State     _state;
    Graphics* _graphics;
    Level*    _level;
};

#endif
