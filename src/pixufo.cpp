#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game  PixUfo;
	Model Background(&PixUfo, "gfx/space_menu_seamless.bmp", 0.0f);
	Model Nebula(&PixUfo, "gfx/nebula_big.bmp", 200.0f);
	Model Player(&PixUfo, "gfx/ufo.bmp", 200.0f);

	bool nebula_direction;

	Uint32 fps = 0;
	float  elapsed_time = 0.0f;
	float  frame_start_time;

	for(;;) // Close the Game after the user's event.
	{
		frame_start_time = SDL_GetTicks() / 1000.0f;

		if(SDL_RenderClear(PixUfo.renderer) != SUCCESS)
		{
			std::cerr << "Can't clean the renderer." << std::endl;
			return 1;
		}
		Background.render(&PixUfo);
		Nebula.render(&PixUfo);
		Player.render(&PixUfo);

		SDL_RenderPresent(PixUfo.renderer);

		if(Nebula.x < Nebula.speed)
		{
			nebula_direction = true;
		}
		else if((Nebula.x + Nebula.geometry.w + Nebula.speed) >= PixUfo.display.w)
		{
			nebula_direction = false;
		}

		if(nebula_direction && ((Nebula.x + Nebula.geometry.w) <= PixUfo.display.w))
		{
			Nebula.x += Nebula.speed;
		}
		else if(Nebula.x >= Nebula.speed)
		{
			Nebula.x -= Nebula.speed;
		}

		SDL_PollEvent(&PixUfo.event);
		switch(PixUfo.event.type)
		{
			default:
			break;

			case SDL_QUIT:
			return 0;

			case SDL_KEYDOWN:
			switch(PixUfo.event.key.keysym.sym)
			{
				default:
				break;

				case SDLK_UP:
				if(Player.y >= Player.speed)
				{
					Player.y -= Player.speed;
				}
				break;

				case SDLK_DOWN:
				if((Player.y + Player.geometry.h + Player.speed) <= PixUfo.display.h)
				{
					Player.y += Player.speed;
				}
				break;

				case SDLK_LEFT:
				if(Player.x >= Player.speed)
				{
					Player.x -= Player.speed;
				}
				break;

				case SDLK_RIGHT:
				if((Player.x + Player.geometry.w + Player.speed) <= PixUfo.display.w)
				{
					Player.x += Player.speed;
				}
				break;
			}
			break;
		}

		if(++fps >= std::numeric_limits<Uint32>::max())
		{
			std::cerr << "Too many frames per second." << std::endl;
			return 1;
		}

		PixUfo.delta_time = ((SDL_GetTicks() / 1000.0f) - frame_start_time);
		if((elapsed_time += PixUfo.delta_time) >= 1.0f)
		{
			fps = 0;
			elapsed_time = 0.0f;
		}
	}
}
