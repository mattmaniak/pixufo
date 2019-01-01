#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game  PixUfo;
	Model Background(&PixUfo, "gfx/space_menu.bmp", 0);
	Model Doctor(&PixUfo, "gfx/doctor.bmp", 0);
	Model Ufo(&PixUfo, "gfx/ufo.bmp", 100);

	while(PixUfo.runtime) // Close the Game after the user's event.
	{
		SDL_PollEvent(&PixUfo.event);
		switch(PixUfo.event.type)
		{
			default:
			break;

			case SDL_QUIT:
			PixUfo.runtime = false;
			break;

			case SDL_KEYDOWN: // TODO: AND KEYUP?
			std::cout << Ufo.x << " and " << Ufo.y << std::endl;

			switch(PixUfo.event.key.keysym.sym)
			{
				default:
				break;

				case SDLK_UP:
				if(Ufo.dimensions.y >= Ufo.speed)
				{
					// Ufo.dimensions.y -= Ufo.speed;
					Ufo.y -= Ufo.speed * FRAME_DELAY;
					Ufo.dimensions.y = Ufo.y;
				}
				break;

				case SDLK_DOWN:
				if((Ufo.dimensions.y + Ufo.dimensions.h + Ufo.speed) <= PixUfo.screen.h)
				{
					// Ufo.dimensions.y += Ufo.speed;
					Ufo.y += Ufo.speed * FRAME_DELAY;
					Ufo.dimensions.y = Ufo.y;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.dimensions.x >= Ufo.speed)
				{
					// Ufo.dimensions.x -= Ufo.speed;
					Ufo.x -= Ufo.speed * FRAME_DELAY;
					Ufo.dimensions.x = Ufo.x;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.dimensions.x + Ufo.dimensions.w + Ufo.speed) <= PixUfo.screen.w)
				{
					// Ufo.dimensions.x += Ufo.speed;
					Ufo.x += Ufo.speed * FRAME_DELAY;
					Ufo.dimensions.x = Ufo.x;
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
		Background.render(PixUfo.renderer, 0, 0);
		Doctor.render(PixUfo.renderer, 120, 120);
		Ufo.render(PixUfo.renderer, Ufo.dimensions.x, Ufo.dimensions.y);

		SDL_RenderPresent(PixUfo.renderer);
	}
}
