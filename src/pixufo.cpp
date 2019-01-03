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

	for(;;) // Close the Game after the user's event.
	{
		if(SDL_GetDisplayMode(0, 0, &PixUfo.display) != SUCCESS)
		{
			std::cerr << "Can't get the current display mode." << std::endl;
			return 1;
		}
		PixUfo.delta_time = 1.0 / static_cast<double>(PixUfo.display.refresh_rate);

		if(Nebula.x < Nebula.speed)
		{
			nebula_direction = true;
		}
		else if((Nebula.x + Nebula.dimensions.w + Nebula.speed) >= PixUfo.display.w)
		{
			nebula_direction = false;
		}

		if(nebula_direction
		&& ((Nebula.x + Nebula.dimensions.w) <= PixUfo.display.w))
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
				if((Ufo.y + Ufo.dimensions.h + Ufo.speed) <= PixUfo.display.h)
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
				if((Ufo.x + Ufo.dimensions.w + Ufo.speed) <= PixUfo.display.w)
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

		// fps++;
		// if(fps > std::numeric_limits<double>::max())
		// {
		// 	std::cerr << "Too many frames per second." << std::endl;
		// 	return 1;
		// }

		// PixUfo.delta_time = (SDL_GetTicks() - frame_start_time) / 1000.0;
		// elapsed_time += PixUfo.delta_time;
		// if(elapsed_time >= 1.0)
		// {
		// 	std::cout << "fps: " << PixUfo.delta_time << std::endl;
		// 	std::cout << PixUfo.screen.refresh_rate << std::endl;
		//
		// 	elapsed_time = 0.0;
		// 	fps = 0.0;
		//
		// }
	}
}
