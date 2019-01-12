#include "graphics.hpp"
#include "game.hpp"
#include "model.hpp"
#include "engine.hpp"
#include "pixufo.hpp"

// Ugly "undefined reference to WinMain" handling.
#ifdef main
#undef main
#endif

int main()
{
	Game   PixUfo;
	Graphics Graphics;
	Model  Background(&Graphics, "space_menu_seamless", 0.0f);
	Model  Nebula(&Graphics, "nebula_medium", 50.0f);
	Model  Player(&Graphics, "ufo", 50.0f);

	const Uint8* pressed_key = SDL_GetKeyboardState(nullptr);
	Uint8 pressed_keys_amount;

	// std::vector<Model> Entities = {}; TODO.
	// bool nebula_direction;

	while(PixUfo.running)
	{
		Graphics.count_frame_start_time();

		if(SDL_RenderClear(Graphics.Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return -1;
		}
		if(Background.render(&Graphics) == -1)
		{
			return -1;
		}
		if(Nebula.render(&Graphics) == -1)
		{
			return -1;
		}
		if(Player.render(&Graphics) == -1)
		{
			return -1;
		}

		SDL_RenderPresent(Graphics.Renderer);

		// TODO: SOMETIMES HIDDEN TEXTURE?
		// if(Nebula.x < Nebula.step)
		// {
		// 	nebula_direction = true;
		// }
		// else if((Nebula.x + Nebula.Geometry.w + Nebula.step) >= Graphics.Screen.w)
		// {
		// 	nebula_direction = false;
		// }
		//
		// if(nebula_direction && ((Nebula.x + Nebula.Geometry.w) <= Graphics.Screen.w))
		// {
		// 	Nebula.x += Nebula.step;
		// }
		// else if(Nebula.x >= Nebula.step)
		// {
		// 	Nebula.x -= Nebula.step;
		// }

		SDL_PollEvent(&PixUfo.event);
		pressed_keys_amount = 0;
		for(Uint8 index = 0; index < std::numeric_limits<Uint8>::max(); index++)
		{
			if(pressed_key[index] == 1)
			{
				pressed_keys_amount++;
			}
		}
		if(pressed_keys_amount > 1)
		{
			Player.step = std::sqrt(Player.step);
		}
		switch(PixUfo.event.type)
		{
			case SDL_QUIT:
			PixUfo.running = false;
			break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			if(pressed_key[SDL_SCANCODE_UP])
			{
				if(Player.y >= Player.step)
				{
					Player.y -= Player.step;
				}
			}
			if(pressed_key[SDL_SCANCODE_DOWN])
			{
				if((Player.y + Player.Geometry.h + Player.step) <= Graphics.Screen.h)
				{
					Player.y += Player.step;
				}
			}
			if(pressed_key[SDL_SCANCODE_LEFT])
			{
				if(Player.x >= Player.step)
				{
					Player.x -= Player.step;
				}
			}
			if(pressed_key[SDL_SCANCODE_RIGHT])
			{
				if((Player.x + Player.Geometry.w + Player.step) <= Graphics.Screen.w)
				{
					Player.x += Player.step;
				}
			}
		}
		if(Graphics.count_elapsed_time() == -1)
		{
			return -1;
		}
	}
	return 0;
}
