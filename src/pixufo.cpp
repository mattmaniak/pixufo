#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

int exit_game()
{
	SDL_Quit();
	return 0;
}

int main()
{
	Menu Menu;

	Keyboard Keyboard;
	if(SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2.");
		return exit_game();
	}
	Graphics Graphics;
	if(!Graphics.is_initialized)
	{
		return exit_game();
	}
	Level Cosmic(Graphics, "background_level", 2);
	if(!Cosmic.is_initialized)
	{
		return exit_game();
	}

	for(;;)
	{
		if(!Graphics.init_frame())
		{
			return false;
		}

		if(Menu.mode == Menu.primary_enabled) // Opened by default.
		{
			if(!Menu.primary(Graphics, Keyboard))
			{
				return exit_game();
			}
			Cosmic.reset();
			if(!Graphics.init_frame()) // Ignored at the first time.
			{
				return false;
			}
		}
		if(!Graphics.render_level(Cosmic, false))
		{
			return exit_game();
		}

		if(!Keyboard.move_player(*Cosmic.Ufo, Menu, Graphics))
		{
			return exit_game();
		}
		physics::check_model_pos(*Cosmic.Ufo);

		for(std::size_t idx = 0; idx < Cosmic.enemies_amount; idx++)
		{
			physics::check_model_pos(*Cosmic.Enemies[idx]);
		}

		if(Menu.mode == Menu.pause_enabled)
		{
			if(!Menu.pause(Graphics, Keyboard, Cosmic))
			{
				return exit_game();
			}
			SDL_Delay(500);
			Graphics.init_frame(); // Prevent entities speed-ups.
		}
		if(!Graphics.clean_renderer())
		{
			return false;
		}
		if(!Graphics.count_fps())
		{
			return exit_game();
		}
	}
	return exit_game();
}
