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
	if(!Graphics.initialized)
	{
		return exit_game();
	}
	Level Cosmic(&Graphics, "background_level", 2);
	if(!Cosmic.initialized)
	{
		return exit_game();
	}

	for(;;)
	{
		Graphics.start_fps_count();

		if(Menu.mode == Menu.primary_enabled) // Opened by default.
		{
			if(!Menu.primary(&Graphics, &Keyboard))
			{
				return exit_game();
			}
			Graphics.start_fps_count(); // Ignored at the first time.
		}
		if(!Graphics.render_level(&Cosmic, false))
		{
			return exit_game();
		}

		if(!Keyboard.move_player(&Cosmic, &Menu))
		{
			return exit_game();
		}
		physics::move_enemies(&Cosmic);
		physics::check_model_pos(Cosmic.Ufo);

		for(std::size_t idx = 0; idx < Cosmic.enemies_amount; idx++)
		{
			physics::check_model_pos(Cosmic.Enemies[idx]);
		}

		if(Menu.mode == Menu.pause_enabled)
		{
			if(!Menu.pause(&Graphics, &Keyboard, &Cosmic))
			{
				return exit_game();
			}
			SDL_Delay(500);
			Graphics.start_fps_count(); // Prevent entities speed-up.
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
