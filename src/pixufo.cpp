#include "pixufo.hpp"
#include "graphics.hpp"
#include "models.hpp"
#include "menus.hpp"
#include "keyboard.hpp"
#include "pause.hpp"
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

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return exit_game();
	}
	Graphics Graphics;
	if(!Graphics.initialized)
	{
		return exit_game();
	}
	Model_background Space(&Graphics, "space_menu_seamless");
	if(!Space.initialized)
	{
		return exit_game();
	}
	Model_player Player(&Graphics, "ufo", 200.0f);
	if(!Player.initialized)
	{
		return exit_game();
	}
	Model_enemy Nebula(&Graphics, "nebula_small", 0.0f);
	if(!Nebula.initialized)
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
		if(SDL_RenderClear(Graphics.Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
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

		if(!Keyboard.handle_ingame(&Player, &Pause.active))
		{
			return exit_game();
		}
		camera::move_entities(&Player, &Space, &Nebula);

		if(Pause.active)
		{
			if(!Pause.launch(&Graphics, &Keyboard, &Menu))
			{
				return exit_game();
			}
			SDL_Delay(500);
			// TODO: ANIMATION OR STH TO PREVENT ENTER ON RETURN TO THE MAIN MENU.
		}

		if(!Graphics.count_elapsed_time())
		{
			return exit_game();
		}
	}
	return exit_game();
}
