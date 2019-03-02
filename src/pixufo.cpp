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

	Graphics_ = new Graphics;
	if(!Graphics_->is_initialized)
	{
		is_initialized = false;
		return;
	}

	Menu_ = new Menu(*Graphics_);
	if(!Menu_->is_initialized)
	{
		is_initialized = false;
		return;
	}
	Keyboard_ = new Keyboard;

	Cosmic_ = new Level(*Graphics_, "background_level", 2);
	if(!Cosmic_->is_initialized)
	{
		is_initialized = false;
		return;
	}
	is_initialized = true;

}

Game::~Game()
{
	if(Graphics_->is_initialized)
	{
		delete Graphics_;
	}
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
		if(!Graphics_->init_frame(*Cosmic_))
		{
			return;
		}
		if(Menu_->mode == Menu_->primary_enabled) // Opened by default.
		{
			if(!Menu_->primary(*Graphics_, *Keyboard_))
			{
				return;
			}
			Cosmic_->reset();
			if(!Graphics_->init_frame(*Cosmic_)) // Ignored at the first time.
			{
				return;
			}
		}
		if(!Graphics_->render_level(*Cosmic_, false))
		{
			return;
		}
		if(!Keyboard_->move_player(*Cosmic_->Ufo, *Menu_, *Graphics_))
		{
			return;
		}

		physics::check_model_pos(*Cosmic_->Ufo);
		if(physics::check_player_collision(*Graphics_, *Cosmic_))
		{
			SDL_Delay(2000);
			return;
		}

		for(std::size_t idx = 0; idx < Cosmic_->enemies_amount; idx++)
		{
			physics::check_model_pos(*Cosmic_->Enemies[idx]);
		}
		if(Menu_->mode == Menu_->pause_enabled)
		{
			if(!Menu_->pause(*Graphics_, *Keyboard_, *Cosmic_))
			{
				return;
			}
			SDL_Delay(500);
			if(!Graphics_->init_frame(*Cosmic_)) // Prevent entities speed-ups.
			{
				return;
			}
		}
		if(!Graphics_->clean_renderer())
		{
			return;
		}
		if(!Graphics_->count_fps())
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
