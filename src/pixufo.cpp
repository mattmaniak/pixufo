#include "pixufo.hpp"
#include "error.hpp"
#include "rendering.hpp"
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
	Rendering Rendering;
	if(!Rendering.initialized)
	{
		return exit_game();
	}
	Level Cosmic(&Rendering, "background1_seamless");
	if(!Cosmic.initialized)
	{
		return exit_game();
	}

	for(;;)
	{
		Rendering.start_fps_count();

		if(Menu.mode == Menu.primary_enabled) // Opened by default.
		{
			if(!Menu.primary(&Rendering, &Keyboard))
			{
				return exit_game();
			}
			SDL_Delay(500);
		}
		if(!Rendering.render_level(&Cosmic))
		{
			return exit_game();
		}

		if(!Keyboard.move_player(&Cosmic, &Menu))
		{
			return exit_game();
		}
		if(Menu.mode == Menu.pause_enabled)
		{
			if(!Menu.pause(&Rendering, &Keyboard))
			{
				return exit_game();
			}
			SDL_Delay(500);
		}
		if(SDL_RenderClear(Rendering.Renderer) != SDL2_SUCCESS)
		{
			error::show_box("Can't clean the renderer in the game loop.");
			return exit_game();
		}
		if(!Rendering.count_fps())
		{
			return exit_game();
		}
	}
	return exit_game();
}
