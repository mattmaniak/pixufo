#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

Game::Game(): state(main_menu)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2 module.");
		throw std::runtime_error("");
	}
	if(TTF_Init() != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2 true type fonts module.");
		throw std::runtime_error("");
	}
	Graphics_ = new Graphics;
	Level_    = new Level(*Graphics_, "background_level", 2);
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
		if(Graphics_->set_up_new_frame())
		{
			Level_->set_entities_borders(*Graphics_); // Changed resolution.
		}
		if(!Level_->Ufo->keyboard_steering(*Graphics_, state))
		{
			return false;
		}

		for(std::size_t idx = 0; idx < Level_->Enemies.size(); idx++)
		{
			Level_->check_entity_pos(*Level_->Enemies[idx]);
		}
		Level_->check_entity_pos(*Level_->Ufo);

		if(Level_->check_player_collision(*Graphics_))
		{
			SDL_Delay(2000);
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
	Main_menu M_menu(*Graphics_);

	while(state == main_menu)
	{
		if(Graphics_->set_up_new_frame())
		{
			// Level_->set_entities_borders(*Graphics_); // Changed resolution.
		}
		if(!M_menu.render(*Graphics_))
		{
			return false;
		}
		if(!M_menu.keyboard_steering(state))
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
	Pause_menu M_menu(*Graphics_);

	while(state == pause_menu)
	{
		if(Graphics_->set_up_new_frame())
		{
			// Level_->set_entities_borders(*Graphics_); // Changed resolution.
		}
		if(!M_menu.render(*Graphics_))
		{
			return false;
		}
		if(!M_menu.keyboard_steering(state))
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
	Credits_menu M_menu(*Graphics_);

	while(state == credits_menu)
	{
		if(Graphics_->set_up_new_frame())
		{
			// Level_->set_entities_borders(*Graphics_); // Changed resolution.
		}
		if(!M_menu.render(*Graphics_))
		{
			return false;
		}
		if(!M_menu.keyboard_steering(state))
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

			case settings_menu:
				if(!Pixufo.level_loop())
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
