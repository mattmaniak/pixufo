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
		is_initialized = false;
		return;
	}
	if(TTF_Init() != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2 ttf module.");
		is_initialized = false;
		return;
	}

	Gfx_ = new Graphics;
	if(!Gfx_->is_initialized)
	{
		is_initialized = false;
		return;
	}

	Menus_ = new Menu(*Gfx_);
	if(!Menus_->is_initialized)
	{
		is_initialized = false;
		return;
	}
	Kboard_ = new Keyboard;

	Cosmic_ = new Level(*Gfx_, "background_level", 2);
	if(!Cosmic_->is_initialized)
	{
		is_initialized = false;
		return;
	}
	is_initialized = true;

}

Game::~Game()
{
	if(Gfx_->is_initialized)
	{
		delete Gfx_;
	}
	if(Cosmic_->is_initialized)
	{
		delete Cosmic_;
	}
	if(!Menus_->is_initialized)
	{
		delete Menus_;
	}
	delete Kboard_;

	TTF_Quit();
	SDL_Quit();
}

void Game::loop()
{
	for(;;)
	{
		if(!Gfx_->init_frame(*Cosmic_))
		{
			return;
		}
		if(Menus_->mode == Menus_->primary_enabled) // Opened by default.
		{
			if(!Menus_->primary(*Gfx_, *Kboard_))
			{
				return;
			}
			Cosmic_->reset();
			if(!Gfx_->init_frame(*Cosmic_)) // Ignored at the first time.
			{
				return;
			}
		}
		if(!Gfx_->render_level(*Cosmic_, false))
		{
			return;
		}
		if(!Kboard_->move_player(*Cosmic_->Ufo, *Menus_, *Gfx_))
		{
			return;
		}

		physics::check_model_pos(*Cosmic_->Ufo);
		if(physics::check_player_collision(*Cosmic_))
		{
			SDL_Delay(2000);
			return;
		}

		for(std::size_t idx = 0; idx < Cosmic_->enemies_amount; idx++)
		{
			physics::check_model_pos(*Cosmic_->Enemies[idx]);
		}
		if(Menus_->mode == Menus_->pause_enabled)
		{
			if(!Menus_->pause(*Gfx_, *Kboard_, *Cosmic_))
			{
				return;
			}
			SDL_Delay(500);
			if(!Gfx_->init_frame(*Cosmic_)) // Prevent entities speed-ups.
			{
				return;
			}
		}
		if(!Gfx_->clean_renderer())
		{
			return;
		}
		if(!Gfx_->count_fps())
		{
			return;
		}
	}
}

int main()
{
	Game Pixufo;

	if(Pixufo.is_initialized)
	{
		Pixufo.loop();
	}
}
