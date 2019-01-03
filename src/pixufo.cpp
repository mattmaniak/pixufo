#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game  PixUfo;
	Model Background(&PixUfo, "gfx/space_menu_seamless.bmp", 0.0);
	Model Nebula(&PixUfo, "gfx/nebula_1.bmp", 200.0);
	Model Ufo(&PixUfo, "gfx/ufo.bmp", 200.0);

	Uint32 fps          = 0;
	Uint32 elapsed_time = 0;

	Uint32 frame_start_time;
	Uint32 delta_time;

	bool nebula_direction;

	for(;;) // Close the Game after the user's event.
	{
		frame_start_time = SDL_GetTicks();

		if(Nebula.x < Nebula.step)
		{
			nebula_direction = true;
		}
		else if((Nebula.x + Nebula.dimensions.w + Nebula.step) >= PixUfo.screen.w)
		{
			nebula_direction = false;
		}

		if(nebula_direction
		&& ((Nebula.x + Nebula.dimensions.w) <= PixUfo.screen.w))
		{
			Nebula.x += Nebula.step;
		}
		else if(Nebula.x >= Nebula.step)
		{
			Nebula.x -= Nebula.step;
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
				if(Ufo.y >= Ufo.step)
				{
					Ufo.y -= Ufo.step;
				}
				break;

				case SDLK_DOWN:
				if((Ufo.y + Ufo.dimensions.h + Ufo.step) <= PixUfo.screen.h)
				{
					Ufo.y += Ufo.step;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.x >= Ufo.step)
				{
					Ufo.x -= Ufo.step;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.x + Ufo.dimensions.w + Ufo.step) <= PixUfo.screen.w)
				{
					Ufo.x += Ufo.step;
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
		Background.render(PixUfo.renderer);
		Nebula.render(PixUfo.renderer);
		Ufo.render(PixUfo.renderer);

		SDL_RenderPresent(PixUfo.renderer);

		fps++;
		if(fps > std::numeric_limits<Uint32>::max())
		{
			std::cerr << "Too many frames per second." << std::endl;
			return 1;
		}

		elapsed_time += (SDL_GetTicks() - frame_start_time);
		if(elapsed_time >= 1000)
		{
			std::cout << "fps: " << fps << std::endl;
			elapsed_time = 0;
			fps = 0;
		}
	}
}
