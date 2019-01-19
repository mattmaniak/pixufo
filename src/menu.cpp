#include "graphics.hpp"
#include "model.hpp"
#include "game.hpp"
#include "menu.hpp"

Button::Button(Graphics* Graphics, const std::string name, const int idx,
               const bool select)
: Model(Graphics, name)
{
	index    = idx;
	selected = select;
}

bool Button::render(Graphics* Graphics)
{
	Geometry.x = (Graphics->Display.w - Geometry.w) / 2;
	Geometry.y = (Graphics->Display.h / 2) + (index * Geometry.h);

	if(!selected)
	{
		SDL_SetTextureAlphaMod(Texture_, 127);
	}
	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Menu::primal(Game* Pixufo, Graphics* Graphics)
{
	Button Play(Graphics, "play", 0, true);
	Button Quit(Graphics, "quit", 1, false);

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

	if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
		return 0;
	}
	Play.render(Graphics);
	Quit.render(Graphics);
	SDL_RenderPresent(Graphics->Renderer);

	while(Pixufo->menu)
	{
		const Uint8* key = SDL_GetKeyboardState(nullptr);

		SDL_PollEvent(&Pixufo->event);
		if(key[SDL_SCANCODE_RETURN])
		{
			Pixufo->menu = false;
		}
	}
	if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

// bool Menu::paused(Game* Pixufo, Graphics* Graphics)
// {
// 	if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
// 	{
// 		std::cerr << SDL_GetError() << std::endl;
// 		return false;
// 	}
// 	return true;
// }

bool Menu::render()
{

	return true;
}
