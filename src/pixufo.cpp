#include "pixufo.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "models.hpp"
#include "menus.hpp"
#include "keyboard.hpp"
#include "pause.hpp"
#include "level.hpp"
#include "camera.hpp"

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
	Keyboard Keyboard;
	Camera   Camera;

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
	Model_background Space(&Graphics, "background1_seamless");
	if(!Space.initialized)
	{
		return exit_game();
	}
	Model_player Player(&Graphics, "ufo", 100.0f);
	if(!Player.initialized)
	{
		return exit_game();
	}
	Model_enemy Nebula(&Graphics, "nebula_big", 0.0f);
	if(!Nebula.initialized)
	{
		return exit_game();
	}
	Level Level(&Graphics, "background1_seamless");
	if(!Level.initialized)
	{
		return exit_game();
	}
	Menu  Menu;
	Pause Pause;

	for(;;)
	{
		if(!Graphics.count_frame_start_time())
		{
			return exit_game();
		}
		if(SDL_RenderClear(Graphics.Renderer) != SDL2_SUCCESS)
		{
			error::show_box("Can't clean the renderer.");
			return exit_game();
		}

		if(Menu.active)
		{
			if(!Menu.launch(&Graphics, &Keyboard))
			{
				return exit_game();
			}
		}
		if(!Space.tile(&Graphics))
		{
			return exit_game();
		}
		if(!Nebula.render(&Graphics))
		{
			return exit_game();
		}

		if(!Player.render(&Graphics))
		{
			return exit_game();
		}
		SDL_RenderPresent(Graphics.Renderer);

		if(!Keyboard.handle_ingame(&Graphics, &Player, &Pause.active, &Level))
		{
			return exit_game();
		}
		if(Pause.active)
		{
			if(!Pause.launch(&Graphics, &Keyboard, &Menu))
			{
				return exit_game();
			}
			SDL_Delay(500);
		}
		Camera.move_entities(&Level, &Player, &Space, &Nebula);

		if(!Graphics.count_elapsed_time())
		{
			return exit_game();
		}
	}
	return exit_game();
}
