#include "game.hpp"
#include "graphics.hpp"
#include "model.hpp"
#include "menu.hpp"
#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

int main()
{
	Game Pixufo;
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
	Model Background(&Graphics, "space_menu_seamless");
	if(!Background.initialized)
	{
		return 0;
	}
	Player Player(&Graphics, "ufo", 50.0f);
	if(!Player.initialized)
	{
		return 0;
	}
	Menu Menu;

	if(!Menu.primal(&Pixufo, &Graphics))
	{
		return 0;
	}

	while(Pixufo.running)
	{
		Graphics.count_frame_start_time();

		if(SDL_RenderClear(Graphics.Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return 0;
		}
		if(!Background.render(&Graphics))
		{
			return 0;
		}
		if(!Player.render(&Graphics))
		{
			return 0;
		}
		SDL_RenderPresent(Graphics.Renderer);
		Pixufo.handle_keyboard(&Player);

		if(!Graphics.count_elapsed_time())
		{
			return 0;
		}
	}
	return 0;
}
