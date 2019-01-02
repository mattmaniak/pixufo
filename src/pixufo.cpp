#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game  PixUfo;
	Model Background(&PixUfo, "gfx/space_menu_seamless.bmp", 0.0);
	Model Nebula(&PixUfo, "gfx/nebula_1.bmp", 100.0);
	Model Ufo(&PixUfo, "gfx/ufo.bmp", 100.0);

	bool nebula_direction;

	while(true) // Close the Game after the user's event.
	{
		if(Nebula.x == 0)
		{
			nebula_direction = true;
		}
		else if((Nebula.x + Nebula.dimensions.w + Nebula.speed) >= PixUfo.screen.w)
		{
			nebula_direction = false;
		}
		std::cout << (Nebula.x + Nebula.dimensions.w + Nebula.speed) << std::endl;

		if(nebula_direction
		&& ((Nebula.x + Nebula.dimensions.w) <= PixUfo.screen.w))
		{
			Nebula.x += Nebula.speed;
		}
		else if((Nebula.x + Nebula.dimensions.w) >= 0)
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
			std::cout << Ufo.x << " and " << Ufo.y << std::endl;

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
				if((Ufo.y + Ufo.dimensions.h + Ufo.speed) <= PixUfo.screen.h)
				{
					Ufo.y += Ufo.speed ;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.x >= Ufo.speed)
				{
					Ufo.x -= Ufo.speed ;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.x + Ufo.dimensions.w + Ufo.speed) <= PixUfo.screen.w)
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
		Background.render(PixUfo.renderer);
		Nebula.render(PixUfo.renderer);
		Ufo.render(PixUfo.renderer);

		SDL_RenderPresent(PixUfo.renderer);
	}
}
