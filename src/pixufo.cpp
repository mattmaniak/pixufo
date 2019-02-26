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

	Gfx = new Graphics;
	if(!Gfx->is_initialized)
	{
		is_initialized = false;
		return;
	}

	Menus  = new Menu;
	Kboard = new Keyboard;

	is_initialized = true;
}

Game::~Game()
{
	if(Gfx->is_initialized)
	{
		delete Gfx;
	}
	delete Menus;
	delete Kboard;

	TTF_Quit();
	SDL_Quit();
}

int main()
{
	Game Pixufo;
	if(!Pixufo.is_initialized)
	{
		return 0;
	}
	Level Cosmic(*Pixufo.Gfx, "background_level", 2);
	if(!Cosmic.is_initialized)
	{
		return 0;
	}

	for(;;)
	{
		if(!Pixufo.Gfx->init_frame())
		{
			return false;
		}
		if(Pixufo.Menus->mode == Pixufo.Menus->primary_enabled) // Opened by default.
		{
			if(!Pixufo.Menus->primary(*Pixufo.Gfx, *Pixufo.Kboard))
			{
				return 0;
			}
			Cosmic.reset();
			if(!Pixufo.Gfx->init_frame()) // Ignored at the first time.
			{
				return false;
			}
		}
		if(!Pixufo.Gfx->render_level(Cosmic, false))
		{
			return 0;
		}
		if(!Pixufo.Kboard->move_player(*Cosmic.Ufo, *Pixufo.Menus, *Pixufo.Gfx))
		{
			return 0;
		}
		physics::check_model_pos(*Cosmic.Ufo);

		for(std::size_t idx = 0; idx < Cosmic.enemies_amount; idx++)
		{
			physics::check_model_pos(*Cosmic.Enemies[idx]);
		}
		if(Pixufo.Menus->mode == Pixufo.Menus->pause_enabled)
		{
			if(!Pixufo.Menus->pause(*Pixufo.Gfx, *Pixufo.Kboard, Cosmic))
			{
				return 0;
			}
			SDL_Delay(500);
			Pixufo.Gfx->init_frame(); // Prevent entities speed-ups.
		}
		if(!Pixufo.Gfx->clean_renderer())
		{
			return 0;
		}
		if(!Pixufo.Gfx->count_fps())
		{
			return 0;
		}
	}
	return 0;
}
