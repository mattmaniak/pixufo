#include "graphics.hpp"
#include "model.hpp"
#include "game.hpp"
#include "pixufo.hpp"

// Very ugly "undefined reference to WinMain" fix.
#ifdef main
#undef main
#endif

int main()
{
	const Uint8* key;
	Uint8        pressed_keys_amount;

	Game PixUfo;
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

	Model Background(&Graphics, "space_menu_seamless", 0.0f);
	if(!Background.initialized)
	{
		return 0;
	}

	Model Player(&Graphics, "ufo", 50.0f);
	if(!Player.initialized)
	{
		return 0;
	}

 	key = SDL_GetKeyboardState(nullptr);

	while(PixUfo.running)
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

		SDL_PollEvent(&PixUfo.event);
		pressed_keys_amount = 0;
		for(Uint8 index = 0; index < std::numeric_limits<Uint8>::max(); index++)
		{
			if(key[index] == 1)
			{
				pressed_keys_amount++;
			}
		}
		if(pressed_keys_amount > 1)
		{
			Player.step = std::sqrt(Player.step);
		}
		PixUfo.handle_keyboard(&Player, key);

		if(Graphics.count_elapsed_time() == -1)
		{
			return 0;
		}
	}
	return 0;
}
