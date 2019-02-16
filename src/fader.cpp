#include "error.hpp"
#include "level.hpp"
#include "menu.hpp"
#include "rendering.hpp"
#include "fader.hpp"
#include "background.hpp"

Fader::Fader(): max_time(500.0f)
{

}

bool Fader::primary_menu_to_level(Rendering* Rendering, Menu* Menu, Level* Level)
{
	beginning_time = SDL_GetTicks();

	while(elapsed_time < max_time)
	{
		if(SDL_RenderClear(Rendering->Renderer) != SDL2_SUCCESS)
		{
			return false;
		}

		elapsed_time = SDL_GetTicks() - beginning_time;

		Menu->Menu_background->pos_x -= (elapsed_time / 100.0f) * Rendering->Display.w;

		std::cout << Menu->Menu_background->pos_x << std::endl;

		if(SDL_RenderCopy(Rendering->Renderer, Menu->Menu_background->Texture, nullptr,
		   &Menu->Menu_background->Geometry) != SDL2_SUCCESS)
		{
			return false;
		}

		SDL_Delay(20);
	}
	return true;
}

bool Fader::level_to_pause_menu()
{

	return true;
}

bool Fader::pause_menu_to_primary_menu()
{

	return true;
}
