#include "game.hpp"
#include "graphics.hpp"
#include "model.hpp"
#include "menu.hpp"
#include "camera.hpp"
#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

int main()
{
	Game Game;
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return 0;
	}
	Graphics Graphics;
	if(!Graphics.initialized)
	{
		return 0;
	}
	Model_background Space(&Graphics, "space_menu_seamless");
	if(!Space.initialized)
	{
		return 0;
	}
	Model_player Player(&Graphics, "ufo", 200.0f);
	if(!Player.initialized)
	{
		return 0;
	}
	Model_enemy Nebula(&Graphics, "nebula_small", 0.0f);
	if(!Nebula.initialized)
	{
		return 0;
	}
	Menu Menu;

	while(Game.running)
	{
		Graphics.count_frame_start_time();

		if(SDL_RenderClear(Graphics.Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return 0;
		}

		if(Game.menu)
		{
			if(!Menu.primal(&Game, &Graphics))
			{
				return 0;
			}
		}
		if(!Space.tile(&Graphics))
		{
			return 0;
		}
		if(!Nebula.render(&Graphics))
		{
			return 0;
		}

		if(!Player.render(&Graphics))
		{
			return 0;
		}
		SDL_RenderPresent(Graphics.Renderer);
		Game.handle_keyboard(&Player);

		camera::move_entities(&Player, &Space, &Nebula);

		if(Game.pause)
		{
			if(!Menu.pause(&Game, &Graphics))
			{
				return 0;
			}
			SDL_Delay(500);
			// TODO: ANIMATION OR STH TO PREVENT ENTER ON RETURN TO THE MAIN MENU.
		}

		if(!Graphics.count_elapsed_time())
		{
			return 0;
		}
	}
	return 0;
}
