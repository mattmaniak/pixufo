#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game  PixUfo;
	Model Background(&PixUfo, "gfx/space_menu_seamless.bmp", 0.0);
	Model Nebula(&PixUfo, "gfx/nebula_big.bmp", 200.0);
	Model Ufo(&PixUfo, "gfx/ufo.bmp", 200.0);

	bool nebula_direction;

	double fps = 0.0;
	double elapsed_time = 0.0;
	double frame_start_time;

	double nebula_start_time = SDL_GetTicks(); // DEBUG.

	// if(SDL_GetDisplayMode(0, 0, &PixUfo.display) != SUCCESS)
	// {
	// 	std::cerr << "Can't get the current display mode." << std::endl;
	// 	return 1;
	// }
	// PixUfo.delta_time = 1.0 / static_cast<double>(PixUfo.display.refresh_rate);

	for(;;) // Close the Game after the user's event.
	{
		frame_start_time = SDL_GetTicks();

		// PixUfo.delta_time = 1.0 / static_cast<double>(PixUfo.display.refresh_rate);

		if(Nebula.x < Nebula.speed)
		{
			nebula_direction = true;
		}
		else if((Nebula.x + Nebula.geometry.w + Nebula.speed) >= PixUfo.display.w)
		{
			nebula_direction = false;
			std::cout << "Nebula time: " << SDL_GetTicks() - nebula_start_time << std::endl;
			return 0;
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
				if(Ufo.y >= Ufo.speed)
				{
					Ufo.y -= Ufo.speed;
				}
				break;

				case SDLK_DOWN:
				if((Ufo.y + Ufo.geometry.h + Ufo.speed) <= PixUfo.display.h)
				{
					Ufo.y += Ufo.speed;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.x >= Ufo.speed)
				{
					Ufo.x -= Ufo.speed;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.x + Ufo.geometry.w + Ufo.speed) <= PixUfo.display.w)
				{
					Ufo.x += Ufo.speed;
				}
				break;
			}
			break;
		}
		if(SDL_RenderClear(PixUfo.renderer) != SUCCESS)
		{
			std::cerr << "Can't clean the renderer." << std::endl;
			return 1;
		}
		Background.render(&PixUfo);
		Nebula.render(&PixUfo);
		Ufo.render(&PixUfo);

		SDL_RenderPresent(PixUfo.renderer);

		if(++fps >= std::numeric_limits<double>::max())
		{
			std::cerr << "Too many frames per second." << std::endl;
			return 1;
		}

		PixUfo.delta_time = (static_cast<double>(SDL_GetTicks()) - frame_start_time) / 1000.0;
		if((elapsed_time += PixUfo.delta_time) >= 1.0)
		{
			std::cout << "delta " << PixUfo.delta_time << std::endl;
			std::cout << fps << std::endl;

			elapsed_time = 0.0;
			fps = 0.0;
		}
	}
}
