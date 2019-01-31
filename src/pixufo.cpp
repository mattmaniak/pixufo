#include "pixufo.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "model.hpp"
#include "menu.hpp"
#include "keyboard.hpp"
#include "level.hpp"

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
	Level* Cosmic = new Level(&Graphics, "background1_seamless");
	if(!Cosmic->initialized)
	{
		delete Cosmic;
		return exit_game();
	}

	for(;;)
	{
		Graphics.start_fps_count();

		if(SDL_RenderClear(Graphics.Renderer) != SDL2_SUCCESS)
		{
			error::show_box("Can't clean the renderer.");
			return exit_game();
		}

		if(Menu.mode == Menu.primary_enabled)
		{
			if(!Menu.primary(&Graphics, &Keyboard))
			{
				return exit_game();
			}
			SDL_Delay(500);
		}
		if(!Graphics.render_level(Cosmic))
		{
			return exit_game();
		}

		if(!Keyboard.handle_ingame(Cosmic, &Menu))
		{
			return exit_game();
		}
		if(Menu.mode == Menu.pause_enabled)
		{
			delete Cosmic;

			if(!Menu.pause(&Graphics, &Keyboard))
			{
				return exit_game();
			}
			SDL_Delay(500);
		}
		if(!Graphics.count_fps())
		{
			return exit_game();
		}
	}
	return exit_game();
}
