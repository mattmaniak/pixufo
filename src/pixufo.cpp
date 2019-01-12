#include "window.hpp"
#include "game.hpp"
#include "model.hpp"
#include "engine.hpp"
#include "pixufo.hpp"

#ifdef main
#undef main
#endif

int main()
{
	Game   PixUfo;
	Window Window;
	Model  Background(&Window, "space_menu_seamless", 0.0f);
	Model  Nebula(&Window, "nebula_medium", 50.0f);
	Model  Player(&Window, "ufo", 50.0f);

	const Uint8* pressed_key = SDL_GetKeyboardState(nullptr);

	// std::vector<Model> Entities = {}; TODO.

	// bool nebula_direction;

	for(;;)
	{
		Window.frame_start_time = SDL_GetTicks() / 1000.0f;

		if(SDL_RenderClear(Window.renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return -1;
		}
		if(Background.render(&Window) == -1)
		{
			return -1;
		}
		if(Nebula.render(&Window) == -1)
		{
			return -1;
		}
		if(Player.render(&Window) == -1)
		{
			return -1;
		}

		SDL_RenderPresent(Window.renderer);

		// TODO: SOMETIMES HIDDEN TEXTURE?
		// if(Nebula.x < Nebula.step)
		// {
		// 	nebula_direction = true;
		// }
		// else if((Nebula.x + Nebula.Geometry.w + Nebula.step) >= Window.Display.w)
		// {
		// 	nebula_direction = false;
		// }
		//
		// if(nebula_direction && ((Nebula.x + Nebula.Geometry.w) <= Window.Display.w))
		// {
		// 	Nebula.x += Nebula.step;
		// }
		// else if(Nebula.x >= Nebula.step)
		// {
		// 	Nebula.x -= Nebula.step;
		// }

		SDL_PollEvent(&PixUfo.event);
		switch(PixUfo.event.type) // TODO: SLASH SPEED - DIVIDE BY 2^(1/2).
		{
			case SDL_QUIT:
			return 0;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			if(pressed_key[SDL_SCANCODE_UP] && (Player.y >= Player.step))
			{
				Player.y -= Player.step;
			}
			if(pressed_key[SDL_SCANCODE_DOWN]
			&& ((Player.y + Player.Geometry.h + Player.step) <= Window.Display.h))
			{
				Player.y += Player.step;
			}
			if(pressed_key[SDL_SCANCODE_LEFT] && (Player.x >= Player.step))
			{
				Player.x -= Player.step;
			}
			if(pressed_key[SDL_SCANCODE_RIGHT]
			&& ((Player.x + Player.Geometry.w + Player.step) <= Window.Display.w))
			{
				Player.x += Player.step;
			}
		}
		if(Window.count_fps() == -1)
		{
			return -1;
		}
	}
	return 0;
}
