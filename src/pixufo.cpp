#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

Game::Game(): state(main_menu)
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
        Graphics_ = new Graphics;
        Level_    = new Level(*Graphics_, "background_level", 2);
    }
    catch(...)
    {
        throw std::runtime_error("");
    }
}

Game::~Game()
{
    delete Graphics_;
    delete Level_;

    TTF_Quit();
    SDL_Quit(); // 38 memleaks here.
}

bool Game::level_loop()
{
    while(state == level)
    {
        if(!Graphics_->set_up_new_frame())
        {
            return false;
        }
        if(!Level_->Ufo->keyboard_steering(*Graphics_, state))
        {
            return false;
        }
        Level_->check_nebulas_pos(*Graphics_);
        Level_->check_ufo_pos();

        if(Level_->check_ufo_collision())
        {
            /* Additional frame to fully cover both models when the collision
            happens. */
            if(!Level_->render(*Graphics_))
            {
                return false;
            }
            SDL_Delay(2000);
            state = main_menu;

            return true;
        }

        Level_->score_points += Graphics_->delta_time_s * 1000.0;
        if(Level_->score_points >= std::numeric_limits<unsigned int>::max())
        {
            throw error::Exception_box("You've reached the score limit.");
            return false;
        }
        if(!Level_->render(*Graphics_))
        {
            return false;
        }
        if(!Graphics_->count_fps())
        {
            return false;
        }
    }
    return true;
}

bool Game::main_menu_loop()
{
    Main_menu Current_menu(*Graphics_);

    while(state == main_menu)
    {
        if(!Graphics_->set_up_new_frame())
        {
            return false;
        }
        if(!Current_menu.render(*Graphics_))
        {
            return false;
        }
        if(!Current_menu.keyboard_steering(state))
        {
            return false;
        }
        if(!Graphics_->count_fps())
        {
            return false;
        }
    }
    Level_->reset();

    return true;
}

bool Game::pause_menu_loop()
{
    Pause_menu Current_menu(*Graphics_);

    while(state == pause_menu)
    {
        if(!Graphics_->set_up_new_frame())
        {
            return false;
        }
        if(!Current_menu.render(*Graphics_))
        {
            return false;
        }
        if(!Current_menu.keyboard_steering(state))
        {
            return false;
        }
        if(!Graphics_->count_fps())
        {
            return false;
        }
    }
    return true;
}

bool Game::credits_menu_loop()
{
    Credits_menu Current_menu(*Graphics_);

    while(state == credits_menu)
    {
        if(!Graphics_->set_up_new_frame())
        {
            return false;
        }
        if(!Current_menu.render(*Graphics_))
        {
            return false;
        }
        if(!Current_menu.keyboard_steering(state))
        {
            return false;
        }
        if(!Graphics_->count_fps())
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
            switch(Pixufo.state)
            {
            case level:
                if(!Pixufo.level_loop())
                {
                    return 0;
                }
                break;

            case main_menu:
                if(!Pixufo.main_menu_loop())
                {
                    return 0;
                }
                break;

            case credits_menu:
                if(!Pixufo.credits_menu_loop())
                {
                    return 0;
                }
                break;

            case pause_menu:
                if(!Pixufo.pause_menu_loop())
                {
                    return 0;
                }
            }
        }
    }
    catch(...) {}
}
