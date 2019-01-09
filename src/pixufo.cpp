#include "window.hpp"
#include "game.hpp"
#include "model.hpp"
#include "pixufo.hpp"

int main()
{
	Game   PixUfo;
	Window Window;
	Model  Background(&Window, "gfx/space_menu_seamless.bmp", 0.0f);
	Model  Nebula(&Window, "gfx/nebula_medium.bmp", 200.0f);
	Model  Player(&Window, "gfx/ufo.bmp", 200.0f);

	// std::vector<Model> Entities = {}; TODO.

	// bool nebula_direction;

	while(PixUfo.running) // Close the Game after the user's event.
	{
		Window.frame_start_time = SDL_GetTicks() / 1000.0f;

		if(SDL_RenderClear(Window.renderer) != SUCCESS)
		{
			std::cerr << "Can't clean the renderer." << std::endl;
			return 1;
		}
		Background.render(&Window);
		Nebula.render(&Window);
		Player.render(&Window);

		SDL_RenderPresent(Window.renderer);

		// TODO: SOMETIMES HIDDEN TEXTURE?
		// if(Nebula.x < Nebula.step)
		// {
		// 	nebula_direction = true;
		// }
		// else if((Nebula.x + Nebula.geometry.w + Nebula.step) >= Window.display.w)
		// {
		// 	nebula_direction = false;
		// }
		//
		// if(nebula_direction && ((Nebula.x + Nebula.geometry.w) <= Window.display.w))
		// {
		// 	Nebula.x += Nebula.step;
		// }
		// else if(Nebula.x >= Nebula.step)
		// {
		// 	Nebula.x -= Nebula.step;
		// }

		SDL_PollEvent(&PixUfo.event);
		switch(PixUfo.event.type)
		{
			default:
			break;

			case SDL_QUIT:
			PixUfo.running = false;
			break;

			case SDL_KEYDOWN:
			switch(PixUfo.event.key.keysym.sym)
			{
				default:
				break;

				case SDLK_UP:
				if(Player.y >= Player.step)
				{
					Player.y -= Player.step;
				}
				break;

				case SDLK_DOWN:
				if((Player.y + Player.geometry.h + Player.step) <= Window.display.h)
				{
					Player.y += Player.step;
				}
				break;

				case SDLK_LEFT:
				if(Player.x >= Player.step)
				{
					Player.x -= Player.step;
				}
				break;

				case SDLK_RIGHT:
				if((Player.x + Player.geometry.w + Player.step) <= Window.display.w)
				{
					Player.x += Player.step;
				}
				break;
			}
			break;
		}
		Window.count_fps();
	}
}
