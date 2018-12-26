#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game  PixUfo;
	Model Ufo(&PixUfo, "gfx/ufo.bmp", 0, 0, 8);

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
			switch(PixUfo.event.key.keysym.sym)
			{
				default:
				break;

				case SDLK_UP:
				if(Ufo.dimensions.y >= Ufo.step)
				{
					Ufo.dimensions.y -= Ufo.step;
				}
				break;

				case SDLK_DOWN:
				if((Ufo.dimensions.y + Ufo.dimensions.h + Ufo.step) <= PixUfo.h)
				{
					Ufo.dimensions.y += Ufo.step;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.dimensions.x >= Ufo.step)
				{
					Ufo.dimensions.x -= Ufo.step;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.dimensions.x + Ufo.dimensions.w + Ufo.step) <= PixUfo.w)
				{
					Ufo.dimensions.x += Ufo.step;
				}
				break;
			}
			break;
		}
		// TODO: CHECKS.
		// Copies and displays the beautiful title.
		if(SDL_RenderClear(PixUfo.renderer) != SUCCESS)
		{
			return 1;
		}
		SDL_RenderCopy(PixUfo.renderer, PixUfo.background, nullptr, nullptr);
		SDL_RenderCopy(PixUfo.renderer, Ufo.texture, nullptr, &Ufo.dimensions);
		SDL_RenderPresent(PixUfo.renderer);

		SDL_UpdateWindowSurface(PixUfo.window);

//		SDL_Delay(FRAME_DELAY);
	}
}
