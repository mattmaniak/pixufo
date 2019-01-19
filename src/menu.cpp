#include "graphics.hpp"
#include "model.hpp"
#include "game.hpp"
#include "menu.hpp"

Button::Button(Graphics* Graphics, const std::string name, const int idx)
: Model(Graphics, name)
{
	index = idx;
}

bool Button::render(Graphics* Graphics, Menu* Menu)
{
	// Centering.
	Geometry.x = (Graphics->Display.w - Geometry.w) / 2;
	Geometry.y = (Graphics->Display.h / 2) + (index * Geometry.h);

	// Shift the selected button.
	if(index == Menu->current_button_index)
	{
		Geometry.x += 64;
	}
	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

Menu::Menu()
{
	current_button_index = 0;
	max_button_index     = 1;
}

bool Menu::primal(Game* Pixufo, Graphics* Graphics)
{
	Button Play(Graphics, "play", 0);
	Button Quit(Graphics, "quit", 1);

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

	while(Pixufo->menu)
	{
		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return 0;
		}
		Play.render(Graphics, this);
		Quit.render(Graphics, this);
		SDL_RenderPresent(Graphics->Renderer);

		handle_keyboard(Pixufo);

		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		if(!Pixufo->running)
		{
			return false;
		}
	}
	return true;
}

void Menu::handle_keyboard(Game* Pixufo)
{
	const Uint8* key = SDL_GetKeyboardState(nullptr);

	SDL_PollEvent(&Pixufo->event);

	if(key[SDL_SCANCODE_UP] && (current_button_index > 0))
	{
		current_button_index--;
	}
	else if(key[SDL_SCANCODE_DOWN] && (current_button_index < max_button_index))
	{
		current_button_index++;
	}
	else if(key[SDL_SCANCODE_RETURN])
	{
		if(current_button_index == 0)
		{
			Pixufo->menu = false;
		}
		else if(current_button_index == 1)
		{
			Pixufo->running = false;
		}
	}
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
