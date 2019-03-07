#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

Game::Game()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2.");
		return;
		// throw std::runtime_error("EXC");
	}
	if(TTF_Init() != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2 true type fonts.");
		return;
		// throw std::runtime_error("EXC");
	}

	Graphics_ = new Graphics;

	Menu_ = new Menu(*Graphics_);
	if(!Menu_->is_initialized)
	{
		return;
	}
	Keyboard_ = new Keyboard;

	Cosmic_ = new Level(*Graphics_, "background_level", 2);
	if(!Cosmic_->is_initialized)
	{
		return;
	}
}

Game::~Game()
{
	delete Graphics_;
	if(Cosmic_->is_initialized)
	{
		delete Cosmic_;
	}
	if(Menu_->is_initialized)
	{
		delete Menu_;
	}
	delete Keyboard_;

	TTF_Quit();
	SDL_Quit();
}

void Game::loop()
{
	for(;;)
	{
		if(!Graphics_->set_up_new_frame())
		{
			Cosmic_->set_entities_borders(*Graphics_);
		}
		if(!Graphics_->clean_renderer())
		{
			return;
		}
		switch(Menu_->mode)
		{
			case Menu_->primary_enabled:
			if(!Menu_->primary(*Graphics_, *Keyboard_))
			{
				return;
			}
			if(!Keyboard_->menu(*Menu_))
			{
				return;
			}
			Graphics_->count_fps();
			Cosmic_->reset();
			break;

			case Menu_->pause_enabled:
			if(!Menu_->pause(*Graphics_, *Keyboard_, *Cosmic_))
			{
				return;
			}
			if(!Keyboard_->pause(*Menu_))
			{
				return;
			}
			// SDL_Delay(500);
			if(!Graphics_->set_up_new_frame()) // Prevent entities speed-ups.
			{
				Cosmic_->set_entities_borders(*Graphics_);
			}
			break;

			case Menu_->all_disabled:
			if(!Cosmic_->Ufo->keyboard_steering(*Menu_, *Graphics_))
			{
				return;
			}

			for(std::size_t idx = 0; idx < Cosmic_->Enemies.size(); idx++)
			{
				Cosmic_->check_entity_pos(*Cosmic_->Enemies[idx]);
			}
			Cosmic_->check_entity_pos(*Cosmic_->Ufo);

			if(Cosmic_->check_player_collision(*Graphics_))
			{
				SDL_Delay(2000);
				return;
			}
			if(!Cosmic_->render(*Graphics_))
			{
				return;
			}
			break;
		}
		if(!Graphics_->count_fps())
		{
			return;
		}
	}
}

int main()
{
	try
	{
		Game Pixufo;
		Pixufo.loop();
	}
	catch(...)
	{

	}
}
