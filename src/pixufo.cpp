#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

Game::Game(): _state(main_menu)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS)
    {
        throw error::Exception_box("Can't initialize the SDL2.");
    }
    if(TTF_Init() != SDL2_SUCCESS)
    {
        throw error::Exception_box("Can't initialize the SDL2 ttf module.");
    }
    try
    {
        _graphics = new Graphics;
        _level    = new Level(*_graphics, "background_level", 2);
    }
    catch(std::runtime_error)
    {
        throw std::runtime_error("Unable to initialize Graphics and/or Level module.");
    }
}

Game::~Game()
{
    delete _graphics;
    delete _level;

    TTF_Quit();
    SDL_Quit(); // 38 memleaks there.
}

State Game::get_state()
{
    return _state;
}

bool Game::level_loop()
{
    while(_state == level)
    {
        if(!_graphics->set_up_new_frame())
        {
            return false;
        }
        if(!_level->Ufo->keyboard_steering(*_graphics, _state))
        {
            return false;
        }
        _level->check_enemies_pos(*_graphics);
        _level->check_ufo_pos();

        if(_level->check_ufo_collision())
        {
            /* Additional frame to fully cover both models when the collision
            happens. */
            if(!_level->render(*_graphics))
            {
                return false;
            }
            SDL_Delay(2000); // Wait a moment after a player's death.
            _state = main_menu;

            return true;
        }

        _level->score_points += _graphics->delta_time_s * 1000.0;
        if(_level->score_points >= std::numeric_limits<unsigned int>::max())
        {
            error::show_box("You've reached the score limit.");
            return false;
        }
        if(!_level->render(*_graphics))
        {
            return false;
        }
        if(!_graphics->count_fps())
        {
            return false;
        }
    }
    return true;
}

bool Game::main_menu_loop()
{
    Main_menu Current_menu(*_graphics); // Unhandled exceptions possible.

    while(_state == main_menu)
    {
        if(!_graphics->set_up_new_frame())
        {
            return false;
        }
        if(!Current_menu.render(*_graphics))
        {
            return false;
        }
        if(!Current_menu.keyboard_steering(_state))
        {
            return false;
        }
        if(!_graphics->count_fps())
        {
            return false;
        }
    }
    _level->reset();

    return true;
}

bool Game::pause_menu_loop()
{
    Pause_menu Current_menu(*_graphics); // Unhandled exceptions possible.

    while(_state == pause_menu)
    {
        if(!_graphics->set_up_new_frame())
        {
            return false;
        }
        if(!Current_menu.render(*_graphics))
        {
            return false;
        }
        if(!Current_menu.keyboard_steering(_state))
        {
            return false;
        }
        if(!_graphics->count_fps())
        {
            return false;
        }
    }
    return true;
}

bool Game::credits_menu_loop()
{
    Credits_menu Current_menu(*_graphics); // Unhandled exceptions possible.

    while(_state == credits_menu)
    {
        if(!_graphics->set_up_new_frame())
        {
            return false;
        }
        if(!Current_menu.render(*_graphics))
        {
            return false;
        }
        if(!Current_menu.keyboard_steering(_state))
        {
            return false;
        }
        if(!_graphics->count_fps())
        {
            return false;
        }
    }
    return true;
}

int main()
{
    try
    {
        Game Pixufo;

        for(;;)
        {
            switch(Pixufo.get_state())
            {
            case level:
                if(!Pixufo.level_loop())
                {
                    return -1;
                }
                break;

            case main_menu:
                if(!Pixufo.main_menu_loop())
                {
                    return -1;
                }
                break;

            case credits_menu:
                if(!Pixufo.credits_menu_loop())
                {
                    return -1;
                }
                break;

            case pause_menu:
                if(!Pixufo.pause_menu_loop())
                {
                    return -1;
                }
            }
        }
    }
    catch(std::runtime_error)
    {
        return -1;
    }
    return 0;
}
