#include "graphics.hpp"
#include "model.hpp"
#include "game.hpp"
#include "menu.hpp"

bool Menu::main(Game* Pixufo, Graphics* Graphics)
{
	const int buttons_amount = 2;

	Model Play(Graphics, "play", 0.0f);
	Model Quit(Graphics, "quit", 0.0f);

	if(!Play.initialized)
	{
		std::cerr << "" << std::endl;
		return false;
	}
	if(!Quit.initialized)
	{
		std::cerr << "" << std::endl;
		return false;
	}

	Play.x = Quit.x = (Graphics->Display.w - Play.Geometry.w) / 2.0f;
	// Quit.x = (Graphics->Display.w - Quit.Geometry.w) / 2.0f;

	Play.y = Graphics->Display.h / 2.0f;
	Quit.y = (Graphics->Display.h / 2.0f) + ((buttons_amount - 1) * Play.Geometry.h);

	while(Pixufo->menu)
	{
		Play.render(Graphics);
		Quit.render(Graphics);
		SDL_RenderPresent(Graphics->Renderer);

		SDL_PollEvent(&Pixufo->event);
		const Uint8* key = SDL_GetKeyboardState(nullptr);
		if(key[SDL_SCANCODE_RETURN])
		{
			Pixufo->menu = false;
		}
		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
	}
	return true;
}

bool Menu::paused(Game* Pixufo, Graphics* Graphics)
{
	if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Menu::render()
{

	return true;
}
